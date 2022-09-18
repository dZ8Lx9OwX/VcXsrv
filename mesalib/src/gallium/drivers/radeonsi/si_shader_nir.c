/*
 * Copyright 2017 Advanced Micro Devices, Inc.
 * All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * on the rights to use, copy, modify, merge, publish, distribute, sub
 * license, and/or sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHOR(S) AND/OR THEIR SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "nir_builder.h"
#include "si_pipe.h"


static bool si_alu_to_scalar_filter(const nir_instr *instr, const void *data)
{
   struct si_screen *sscreen = (struct si_screen *)data;

   if (sscreen->info.has_packed_math_16bit && instr->type == nir_instr_type_alu) {
      nir_alu_instr *alu = nir_instr_as_alu(instr);

      if (alu->dest.dest.is_ssa &&
          alu->dest.dest.ssa.bit_size == 16 &&
          alu->dest.dest.ssa.num_components == 2)
         return false;
   }

   return true;
}

static uint8_t si_vectorize_callback(const nir_instr *instr, const void *data)
{
   if (instr->type != nir_instr_type_alu)
      return 0;

   nir_alu_instr *alu = nir_instr_as_alu(instr);
   if (nir_dest_bit_size(alu->dest.dest) == 16)
      return 2;

   return 1;
}

void si_nir_opts(struct si_screen *sscreen, struct nir_shader *nir, bool first)
{
   bool progress;

   do {
      progress = false;
      bool lower_alu_to_scalar = false;
      bool lower_phis_to_scalar = false;

      NIR_PASS(progress, nir, nir_lower_vars_to_ssa);
      NIR_PASS(progress, nir, nir_lower_alu_to_scalar, si_alu_to_scalar_filter, sscreen);
      NIR_PASS(progress, nir, nir_lower_phis_to_scalar, false);

      if (first) {
         NIR_PASS(progress, nir, nir_split_array_vars, nir_var_function_temp);
         NIR_PASS(lower_alu_to_scalar, nir, nir_shrink_vec_array_vars, nir_var_function_temp);
         NIR_PASS(progress, nir, nir_opt_find_array_copies);
      }
      NIR_PASS(progress, nir, nir_opt_copy_prop_vars);
      NIR_PASS(progress, nir, nir_opt_dead_write_vars);

      NIR_PASS(lower_alu_to_scalar, nir, nir_opt_trivial_continues);
      /* (Constant) copy propagation is needed for txf with offsets. */
      NIR_PASS(progress, nir, nir_copy_prop);
      NIR_PASS(progress, nir, nir_opt_remove_phis);
      NIR_PASS(progress, nir, nir_opt_dce);
      /* nir_opt_if_optimize_phi_true_false is disabled on LLVM14 (#6976) */
      NIR_PASS(lower_phis_to_scalar, nir, nir_opt_if,
         nir_opt_if_aggressive_last_continue |
            (LLVM_VERSION_MAJOR == 14 ? 0 : nir_opt_if_optimize_phi_true_false));
      NIR_PASS(progress, nir, nir_opt_dead_cf);

      if (lower_alu_to_scalar)
         NIR_PASS_V(nir, nir_lower_alu_to_scalar, si_alu_to_scalar_filter, sscreen);
      if (lower_phis_to_scalar)
         NIR_PASS_V(nir, nir_lower_phis_to_scalar, false);
      progress |= lower_alu_to_scalar | lower_phis_to_scalar;

      NIR_PASS(progress, nir, nir_opt_cse);
      NIR_PASS(progress, nir, nir_opt_peephole_select, 8, true, true);

      /* Needed for algebraic lowering */
      NIR_PASS(progress, nir, nir_opt_algebraic);
      NIR_PASS(progress, nir, nir_opt_constant_folding);

      if (!nir->info.flrp_lowered) {
         unsigned lower_flrp = (nir->options->lower_flrp16 ? 16 : 0) |
                               (nir->options->lower_flrp32 ? 32 : 0) |
                               (nir->options->lower_flrp64 ? 64 : 0);
         assert(lower_flrp);
         bool lower_flrp_progress = false;

         NIR_PASS(lower_flrp_progress, nir, nir_lower_flrp, lower_flrp, false /* always_precise */);
         if (lower_flrp_progress) {
            NIR_PASS(progress, nir, nir_opt_constant_folding);
            progress = true;
         }

         /* Nothing should rematerialize any flrps, so we only
          * need to do this lowering once.
          */
         nir->info.flrp_lowered = true;
      }

      NIR_PASS(progress, nir, nir_opt_undef);
      NIR_PASS(progress, nir, nir_opt_conditional_discard);
      if (nir->options->max_unroll_iterations) {
         NIR_PASS(progress, nir, nir_opt_loop_unroll);
      }

      if (nir->info.stage == MESA_SHADER_FRAGMENT)
         NIR_PASS_V(nir, nir_opt_move_discards_to_top);

      if (sscreen->info.has_packed_math_16bit)
         NIR_PASS(progress, nir, nir_opt_vectorize, si_vectorize_callback, NULL);
   } while (progress);

   NIR_PASS_V(nir, nir_lower_var_copies);
}

void si_nir_late_opts(nir_shader *nir)
{
   bool more_late_algebraic = true;
   while (more_late_algebraic) {
      more_late_algebraic = false;
      NIR_PASS(more_late_algebraic, nir, nir_opt_algebraic_late);
      NIR_PASS_V(nir, nir_opt_constant_folding);

      /* We should run this after constant folding for stages that support indirect
       * inputs/outputs.
       */
      if (nir->options->support_indirect_inputs & BITFIELD_BIT(nir->info.stage) ||
          nir->options->support_indirect_outputs & BITFIELD_BIT(nir->info.stage))
         NIR_PASS_V(nir, nir_io_add_const_offset_to_base, nir_var_shader_in | nir_var_shader_out);

      NIR_PASS_V(nir, nir_copy_prop);
      NIR_PASS_V(nir, nir_opt_dce);
      NIR_PASS_V(nir, nir_opt_cse);
   }
}

static void si_late_optimize_16bit_samplers(struct si_screen *sscreen, nir_shader *nir)
{
   /* Optimize types of image_sample sources and destinations.
    *
    * The image_sample sources bit sizes are:
    *   nir_tex_src_coord:       a16 ? 16 : 32
    *   nir_tex_src_comparator:  32
    *   nir_tex_src_offset:      32
    *   nir_tex_src_bias:        a16 ? 16 : 32
    *   nir_tex_src_lod:         a16 ? 16 : 32
    *   nir_tex_src_min_lod:     a16 ? 16 : 32
    *   nir_tex_src_ms_index:    a16 ? 16 : 32
    *   nir_tex_src_ddx:         has_g16 ? (g16 ? 16 : 32) : (a16 ? 16 : 32)
    *   nir_tex_src_ddy:         has_g16 ? (g16 ? 16 : 32) : (a16 ? 16 : 32)
    *
    * We only use a16/g16 if all of the affected sources are 16bit.
    */
   bool has_g16 = sscreen->info.gfx_level >= GFX10 && LLVM_VERSION_MAJOR >= 12;
   struct nir_fold_tex_srcs_options fold_srcs_options[] = {
      {
         .sampler_dims =
            ~(BITFIELD_BIT(GLSL_SAMPLER_DIM_CUBE) | BITFIELD_BIT(GLSL_SAMPLER_DIM_BUF)),
         .src_types = (1 << nir_tex_src_coord) | (1 << nir_tex_src_lod) |
                      (1 << nir_tex_src_bias) | (1 << nir_tex_src_min_lod) |
                      (1 << nir_tex_src_ms_index) |
                      (has_g16 ? 0 : (1 << nir_tex_src_ddx) | (1 << nir_tex_src_ddy)),
      },
      {
         .sampler_dims = ~BITFIELD_BIT(GLSL_SAMPLER_DIM_CUBE),
         .src_types = (1 << nir_tex_src_ddx) | (1 << nir_tex_src_ddy),
      },
   };
   struct nir_fold_16bit_tex_image_options fold_16bit_options = {
      .rounding_mode = nir_rounding_mode_rtne,
      .fold_tex_dest = true,
      .fold_image_load_store_data = true,
      .fold_srcs_options_count = has_g16 ? 2 : 1,
      .fold_srcs_options = fold_srcs_options,
   };
   bool changed = false;
   NIR_PASS(changed, nir, nir_fold_16bit_tex_image, &fold_16bit_options);

   if (changed) {
      si_nir_opts(sscreen, nir, false);
      si_nir_late_opts(nir);
   }
}

static bool
lower_intrinsic_filter(const nir_instr *instr, const void *dummy)
{
   return instr->type == nir_instr_type_intrinsic;
}

static nir_ssa_def *
lower_intrinsic_instr(nir_builder *b, nir_instr *instr, void *dummy)
{
   nir_intrinsic_instr *intrin = nir_instr_as_intrinsic(instr);

   switch (intrin->intrinsic) {
   case nir_intrinsic_is_sparse_texels_resident:
      /* code==0 means sparse texels are resident */
      return nir_ieq_imm(b, intrin->src[0].ssa, 0);
   case nir_intrinsic_sparse_residency_code_and:
      return nir_ior(b, intrin->src[0].ssa, intrin->src[1].ssa);
   default:
      return NULL;
   }
}

static bool si_lower_intrinsics(nir_shader *nir)
{
   return nir_shader_lower_instructions(nir,
                                        lower_intrinsic_filter,
                                        lower_intrinsic_instr,
                                        NULL);
}

/**
 * Perform "lowering" operations on the NIR that are run once when the shader
 * selector is created.
 */
static void si_lower_nir(struct si_screen *sscreen, struct nir_shader *nir)
{
   /* Perform lowerings (and optimizations) of code.
    *
    * Performance considerations aside, we must:
    * - lower certain ALU operations
    * - ensure constant offsets for texture instructions are folded
    *   and copy-propagated
    */

   static const struct nir_lower_tex_options lower_tex_options = {
      .lower_txp = ~0u,
      .lower_txs_cube_array = true,
      .lower_invalid_implicit_lod = true,
      .lower_tg4_offsets = true,
   };
   NIR_PASS_V(nir, nir_lower_tex, &lower_tex_options);

   static const struct nir_lower_image_options lower_image_options = {
      .lower_cube_size = true,
   };
   NIR_PASS_V(nir, nir_lower_image, &lower_image_options);

   NIR_PASS_V(nir, si_lower_intrinsics);

   const nir_lower_subgroups_options subgroups_options = {
      .subgroup_size = 64,
      .ballot_bit_size = 64,
      .ballot_components = 1,
      .lower_to_scalar = true,
      .lower_subgroup_masks = true,
      .lower_vote_trivial = false,
      .lower_vote_eq = true,
   };
   NIR_PASS_V(nir, nir_lower_subgroups, &subgroups_options);

   NIR_PASS_V(nir, nir_lower_discard_or_demote,
              (sscreen->debug_flags & DBG(FS_CORRECT_DERIVS_AFTER_KILL)) ||
               nir->info.use_legacy_math_rules);

   /* Lower load constants to scalar and then clean up the mess */
   NIR_PASS_V(nir, nir_lower_load_const_to_scalar);
   NIR_PASS_V(nir, nir_lower_var_copies);
   NIR_PASS_V(nir, nir_opt_intrinsics);
   NIR_PASS_V(nir, nir_lower_system_values);
   NIR_PASS_V(nir, nir_lower_compute_system_values, NULL);

   /* si_nir_kill_outputs and ac_nir_optimize_outputs require outputs to be scalar. */
   if (nir->info.stage == MESA_SHADER_VERTEX ||
       nir->info.stage == MESA_SHADER_TESS_EVAL ||
       nir->info.stage == MESA_SHADER_GEOMETRY)
      NIR_PASS_V(nir, nir_lower_io_to_scalar, nir_var_shader_out);

   if (nir->info.stage == MESA_SHADER_COMPUTE) {
      if (nir->info.cs.derivative_group == DERIVATIVE_GROUP_QUADS) {
         /* If we are shuffling local_invocation_id for quad derivatives, we
          * need to derive local_invocation_index from local_invocation_id
          * first, so that the value corresponds to the shuffled
          * local_invocation_id.
          */
         nir_lower_compute_system_values_options options = {0};
         options.lower_local_invocation_index = true;
         NIR_PASS_V(nir, nir_lower_compute_system_values, &options);
      }

      nir_opt_cse(nir); /* CSE load_local_invocation_id */
      nir_lower_compute_system_values_options options = {0};
      options.shuffle_local_ids_for_quad_derivatives = true;
      NIR_PASS_V(nir, nir_lower_compute_system_values, &options);
   }

   if (sscreen->b.get_shader_param(&sscreen->b, PIPE_SHADER_FRAGMENT, PIPE_SHADER_CAP_FP16)) {
      NIR_PASS_V(nir, nir_lower_mediump_io,
                 /* TODO: LLVM fails to compile this test if VS inputs are 16-bit:
                  * dEQP-GLES31.functional.shaders.builtin_functions.integer.bitfieldinsert.uvec3_lowp_geometry
                  */
                 (nir->info.stage != MESA_SHADER_VERTEX ? nir_var_shader_in : 0) | nir_var_shader_out,
                 BITFIELD64_BIT(VARYING_SLOT_PNTC) | BITFIELD64_RANGE(VARYING_SLOT_VAR0, 32),
                 true);
   }

   si_nir_opts(sscreen, nir, true);
   /* Run late optimizations to fuse ffma and eliminate 16-bit conversions. */
   si_nir_late_opts(nir);

   if (sscreen->b.get_shader_param(&sscreen->b, PIPE_SHADER_FRAGMENT, PIPE_SHADER_CAP_FP16))
      si_late_optimize_16bit_samplers(sscreen, nir);

   NIR_PASS_V(nir, nir_remove_dead_variables, nir_var_function_temp, NULL);
}

char *si_finalize_nir(struct pipe_screen *screen, void *nirptr)
{
   struct si_screen *sscreen = (struct si_screen *)screen;
   struct nir_shader *nir = (struct nir_shader *)nirptr;

   nir_lower_io_passes(nir);

   /* Remove dead derefs, so that we can remove uniforms. */
   NIR_PASS_V(nir, nir_opt_dce);

   /* Remove uniforms because those should have been lowered to UBOs already. */
   nir_foreach_variable_with_modes_safe(var, nir, nir_var_uniform) {
      if (!glsl_type_get_image_count(var->type) &&
          !glsl_type_get_sampler_count(var->type))
         exec_node_remove(&var->node);
   }

   si_lower_nir(sscreen, nir);
   nir_shader_gather_info(nir, nir_shader_get_entrypoint(nir));

   if (sscreen->options.inline_uniforms)
      nir_find_inlinable_uniforms(nir);

   /* Lower large variables that are always constant with load_constant intrinsics, which
    * get turned into PC-relative loads from a data section next to the shader.
    *
    * Run this once before lcssa because the added phis may prevent this
    * pass from operating correctly.
    *
    * nir_opt_large_constants may use op_amul (see nir_build_deref_offset),
    * or may create unneeded code, so run si_nir_opts if needed.
    */
   NIR_PASS_V(nir, nir_remove_dead_variables, nir_var_function_temp, NULL);
   bool progress = false;
   NIR_PASS(progress, nir, nir_opt_large_constants, glsl_get_natural_size_align_bytes, 16);
   if (progress)
      si_nir_opts(sscreen, nir, false);

   NIR_PASS_V(nir, nir_convert_to_lcssa, true, true); /* required by divergence analysis */
   NIR_PASS_V(nir, nir_divergence_analysis); /* to find divergent loops */

   return NULL;
}
