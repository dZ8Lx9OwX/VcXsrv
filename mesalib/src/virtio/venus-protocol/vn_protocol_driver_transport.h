/* This file is generated by venus-protocol.  See vn_protocol_driver.h. */

/*
 * Copyright 2020 Google LLC
 * SPDX-License-Identifier: MIT
 */

#ifndef VN_PROTOCOL_DRIVER_TRANSPORT_H
#define VN_PROTOCOL_DRIVER_TRANSPORT_H

#include "vn_instance.h"
#include "vn_protocol_driver_structs.h"

/* struct VkCommandStreamDescriptionMESA */

static inline size_t
vn_sizeof_VkCommandStreamDescriptionMESA(const VkCommandStreamDescriptionMESA *val)
{
    size_t size = 0;
    size += vn_sizeof_uint32_t(&val->resourceId);
    size += vn_sizeof_size_t(&val->offset);
    size += vn_sizeof_size_t(&val->size);
    return size;
}

static inline void
vn_encode_VkCommandStreamDescriptionMESA(struct vn_cs_encoder *enc, const VkCommandStreamDescriptionMESA *val)
{
    vn_encode_uint32_t(enc, &val->resourceId);
    vn_encode_size_t(enc, &val->offset);
    vn_encode_size_t(enc, &val->size);
}

/* struct VkCommandStreamDependencyMESA */

static inline size_t
vn_sizeof_VkCommandStreamDependencyMESA(const VkCommandStreamDependencyMESA *val)
{
    size_t size = 0;
    size += vn_sizeof_uint32_t(&val->srcCommandStream);
    size += vn_sizeof_uint32_t(&val->dstCommandStream);
    return size;
}

static inline void
vn_encode_VkCommandStreamDependencyMESA(struct vn_cs_encoder *enc, const VkCommandStreamDependencyMESA *val)
{
    vn_encode_uint32_t(enc, &val->srcCommandStream);
    vn_encode_uint32_t(enc, &val->dstCommandStream);
}

/* struct VkRingCreateInfoMESA chain */

static inline size_t
vn_sizeof_VkRingCreateInfoMESA_pnext(const void *val)
{
    /* no known/supported struct */
    return vn_sizeof_simple_pointer(NULL);
}

static inline size_t
vn_sizeof_VkRingCreateInfoMESA_self(const VkRingCreateInfoMESA *val)
{
    size_t size = 0;
    /* skip val->{sType,pNext} */
    size += vn_sizeof_VkFlags(&val->flags);
    size += vn_sizeof_uint32_t(&val->resourceId);
    size += vn_sizeof_size_t(&val->offset);
    size += vn_sizeof_size_t(&val->size);
    size += vn_sizeof_uint64_t(&val->idleTimeout);
    size += vn_sizeof_size_t(&val->headOffset);
    size += vn_sizeof_size_t(&val->tailOffset);
    size += vn_sizeof_size_t(&val->statusOffset);
    size += vn_sizeof_size_t(&val->bufferOffset);
    size += vn_sizeof_size_t(&val->bufferSize);
    size += vn_sizeof_size_t(&val->extraOffset);
    size += vn_sizeof_size_t(&val->extraSize);
    return size;
}

static inline size_t
vn_sizeof_VkRingCreateInfoMESA(const VkRingCreateInfoMESA *val)
{
    size_t size = 0;

    size += vn_sizeof_VkStructureType(&val->sType);
    size += vn_sizeof_VkRingCreateInfoMESA_pnext(val->pNext);
    size += vn_sizeof_VkRingCreateInfoMESA_self(val);

    return size;
}

static inline void
vn_encode_VkRingCreateInfoMESA_pnext(struct vn_cs_encoder *enc, const void *val)
{
    /* no known/supported struct */
    vn_encode_simple_pointer(enc, NULL);
}

static inline void
vn_encode_VkRingCreateInfoMESA_self(struct vn_cs_encoder *enc, const VkRingCreateInfoMESA *val)
{
    /* skip val->{sType,pNext} */
    vn_encode_VkFlags(enc, &val->flags);
    vn_encode_uint32_t(enc, &val->resourceId);
    vn_encode_size_t(enc, &val->offset);
    vn_encode_size_t(enc, &val->size);
    vn_encode_uint64_t(enc, &val->idleTimeout);
    vn_encode_size_t(enc, &val->headOffset);
    vn_encode_size_t(enc, &val->tailOffset);
    vn_encode_size_t(enc, &val->statusOffset);
    vn_encode_size_t(enc, &val->bufferOffset);
    vn_encode_size_t(enc, &val->bufferSize);
    vn_encode_size_t(enc, &val->extraOffset);
    vn_encode_size_t(enc, &val->extraSize);
}

static inline void
vn_encode_VkRingCreateInfoMESA(struct vn_cs_encoder *enc, const VkRingCreateInfoMESA *val)
{
    assert(val->sType == VK_STRUCTURE_TYPE_RING_CREATE_INFO_MESA);
    vn_encode_VkStructureType(enc, &(VkStructureType){ VK_STRUCTURE_TYPE_RING_CREATE_INFO_MESA });
    vn_encode_VkRingCreateInfoMESA_pnext(enc, val->pNext);
    vn_encode_VkRingCreateInfoMESA_self(enc, val);
}

static inline size_t vn_sizeof_vkSetReplyCommandStreamMESA(const VkCommandStreamDescriptionMESA* pStream)
{
    const VkCommandTypeEXT cmd_type = VK_COMMAND_TYPE_vkSetReplyCommandStreamMESA_EXT;
    const VkFlags cmd_flags = 0;
    size_t cmd_size = vn_sizeof_VkCommandTypeEXT(&cmd_type) + vn_sizeof_VkFlags(&cmd_flags);

    cmd_size += vn_sizeof_simple_pointer(pStream);
    if (pStream)
        cmd_size += vn_sizeof_VkCommandStreamDescriptionMESA(pStream);

    return cmd_size;
}

static inline void vn_encode_vkSetReplyCommandStreamMESA(struct vn_cs_encoder *enc, VkCommandFlagsEXT cmd_flags, const VkCommandStreamDescriptionMESA* pStream)
{
    const VkCommandTypeEXT cmd_type = VK_COMMAND_TYPE_vkSetReplyCommandStreamMESA_EXT;

    vn_encode_VkCommandTypeEXT(enc, &cmd_type);
    vn_encode_VkFlags(enc, &cmd_flags);

    if (vn_encode_simple_pointer(enc, pStream))
        vn_encode_VkCommandStreamDescriptionMESA(enc, pStream);
}

static inline size_t vn_sizeof_vkSetReplyCommandStreamMESA_reply(const VkCommandStreamDescriptionMESA* pStream)
{
    const VkCommandTypeEXT cmd_type = VK_COMMAND_TYPE_vkSetReplyCommandStreamMESA_EXT;
    size_t cmd_size = vn_sizeof_VkCommandTypeEXT(&cmd_type);

    /* skip pStream */

    return cmd_size;
}

static inline void vn_decode_vkSetReplyCommandStreamMESA_reply(struct vn_cs_decoder *dec, const VkCommandStreamDescriptionMESA* pStream)
{
    VkCommandTypeEXT command_type;
    vn_decode_VkCommandTypeEXT(dec, &command_type);
    assert(command_type == VK_COMMAND_TYPE_vkSetReplyCommandStreamMESA_EXT);

    /* skip pStream */
}

static inline size_t vn_sizeof_vkSeekReplyCommandStreamMESA(size_t position)
{
    const VkCommandTypeEXT cmd_type = VK_COMMAND_TYPE_vkSeekReplyCommandStreamMESA_EXT;
    const VkFlags cmd_flags = 0;
    size_t cmd_size = vn_sizeof_VkCommandTypeEXT(&cmd_type) + vn_sizeof_VkFlags(&cmd_flags);

    cmd_size += vn_sizeof_size_t(&position);

    return cmd_size;
}

static inline void vn_encode_vkSeekReplyCommandStreamMESA(struct vn_cs_encoder *enc, VkCommandFlagsEXT cmd_flags, size_t position)
{
    const VkCommandTypeEXT cmd_type = VK_COMMAND_TYPE_vkSeekReplyCommandStreamMESA_EXT;

    vn_encode_VkCommandTypeEXT(enc, &cmd_type);
    vn_encode_VkFlags(enc, &cmd_flags);

    vn_encode_size_t(enc, &position);
}

static inline size_t vn_sizeof_vkSeekReplyCommandStreamMESA_reply(size_t position)
{
    const VkCommandTypeEXT cmd_type = VK_COMMAND_TYPE_vkSeekReplyCommandStreamMESA_EXT;
    size_t cmd_size = vn_sizeof_VkCommandTypeEXT(&cmd_type);

    /* skip position */

    return cmd_size;
}

static inline void vn_decode_vkSeekReplyCommandStreamMESA_reply(struct vn_cs_decoder *dec, size_t position)
{
    VkCommandTypeEXT command_type;
    vn_decode_VkCommandTypeEXT(dec, &command_type);
    assert(command_type == VK_COMMAND_TYPE_vkSeekReplyCommandStreamMESA_EXT);

    /* skip position */
}

static inline size_t vn_sizeof_vkExecuteCommandStreamsMESA(uint32_t streamCount, const VkCommandStreamDescriptionMESA* pStreams, const size_t* pReplyPositions, uint32_t dependencyCount, const VkCommandStreamDependencyMESA* pDependencies, VkCommandStreamExecutionFlagsMESA flags)
{
    const VkCommandTypeEXT cmd_type = VK_COMMAND_TYPE_vkExecuteCommandStreamsMESA_EXT;
    const VkFlags cmd_flags = 0;
    size_t cmd_size = vn_sizeof_VkCommandTypeEXT(&cmd_type) + vn_sizeof_VkFlags(&cmd_flags);

    cmd_size += vn_sizeof_uint32_t(&streamCount);
    if (pStreams) {
        cmd_size += vn_sizeof_array_size(streamCount);
        for (uint32_t i = 0; i < streamCount; i++)
            cmd_size += vn_sizeof_VkCommandStreamDescriptionMESA(&pStreams[i]);
    } else {
        cmd_size += vn_sizeof_array_size(0);
    }
    if (pReplyPositions) {
        cmd_size += vn_sizeof_array_size(streamCount);
        cmd_size += vn_sizeof_size_t_array(pReplyPositions, streamCount);
    } else {
        cmd_size += vn_sizeof_array_size(0);
    }
    cmd_size += vn_sizeof_uint32_t(&dependencyCount);
    if (pDependencies) {
        cmd_size += vn_sizeof_array_size(dependencyCount);
        for (uint32_t i = 0; i < dependencyCount; i++)
            cmd_size += vn_sizeof_VkCommandStreamDependencyMESA(&pDependencies[i]);
    } else {
        cmd_size += vn_sizeof_array_size(0);
    }
    cmd_size += vn_sizeof_VkFlags(&flags);

    return cmd_size;
}

static inline void vn_encode_vkExecuteCommandStreamsMESA(struct vn_cs_encoder *enc, VkCommandFlagsEXT cmd_flags, uint32_t streamCount, const VkCommandStreamDescriptionMESA* pStreams, const size_t* pReplyPositions, uint32_t dependencyCount, const VkCommandStreamDependencyMESA* pDependencies, VkCommandStreamExecutionFlagsMESA flags)
{
    const VkCommandTypeEXT cmd_type = VK_COMMAND_TYPE_vkExecuteCommandStreamsMESA_EXT;

    vn_encode_VkCommandTypeEXT(enc, &cmd_type);
    vn_encode_VkFlags(enc, &cmd_flags);

    vn_encode_uint32_t(enc, &streamCount);
    if (pStreams) {
        vn_encode_array_size(enc, streamCount);
        for (uint32_t i = 0; i < streamCount; i++)
            vn_encode_VkCommandStreamDescriptionMESA(enc, &pStreams[i]);
    } else {
        vn_encode_array_size(enc, 0);
    }
    if (pReplyPositions) {
        vn_encode_array_size(enc, streamCount);
        vn_encode_size_t_array(enc, pReplyPositions, streamCount);
    } else {
        vn_encode_array_size(enc, 0);
    }
    vn_encode_uint32_t(enc, &dependencyCount);
    if (pDependencies) {
        vn_encode_array_size(enc, dependencyCount);
        for (uint32_t i = 0; i < dependencyCount; i++)
            vn_encode_VkCommandStreamDependencyMESA(enc, &pDependencies[i]);
    } else {
        vn_encode_array_size(enc, 0);
    }
    vn_encode_VkFlags(enc, &flags);
}

static inline size_t vn_sizeof_vkExecuteCommandStreamsMESA_reply(uint32_t streamCount, const VkCommandStreamDescriptionMESA* pStreams, const size_t* pReplyPositions, uint32_t dependencyCount, const VkCommandStreamDependencyMESA* pDependencies, VkCommandStreamExecutionFlagsMESA flags)
{
    const VkCommandTypeEXT cmd_type = VK_COMMAND_TYPE_vkExecuteCommandStreamsMESA_EXT;
    size_t cmd_size = vn_sizeof_VkCommandTypeEXT(&cmd_type);

    /* skip streamCount */
    /* skip pStreams */
    /* skip pReplyPositions */
    /* skip dependencyCount */
    /* skip pDependencies */
    /* skip flags */

    return cmd_size;
}

static inline void vn_decode_vkExecuteCommandStreamsMESA_reply(struct vn_cs_decoder *dec, uint32_t streamCount, const VkCommandStreamDescriptionMESA* pStreams, const size_t* pReplyPositions, uint32_t dependencyCount, const VkCommandStreamDependencyMESA* pDependencies, VkCommandStreamExecutionFlagsMESA flags)
{
    VkCommandTypeEXT command_type;
    vn_decode_VkCommandTypeEXT(dec, &command_type);
    assert(command_type == VK_COMMAND_TYPE_vkExecuteCommandStreamsMESA_EXT);

    /* skip streamCount */
    /* skip pStreams */
    /* skip pReplyPositions */
    /* skip dependencyCount */
    /* skip pDependencies */
    /* skip flags */
}

static inline size_t vn_sizeof_vkCreateRingMESA(uint64_t ring, const VkRingCreateInfoMESA* pCreateInfo)
{
    const VkCommandTypeEXT cmd_type = VK_COMMAND_TYPE_vkCreateRingMESA_EXT;
    const VkFlags cmd_flags = 0;
    size_t cmd_size = vn_sizeof_VkCommandTypeEXT(&cmd_type) + vn_sizeof_VkFlags(&cmd_flags);

    cmd_size += vn_sizeof_uint64_t(&ring);
    cmd_size += vn_sizeof_simple_pointer(pCreateInfo);
    if (pCreateInfo)
        cmd_size += vn_sizeof_VkRingCreateInfoMESA(pCreateInfo);

    return cmd_size;
}

static inline void vn_encode_vkCreateRingMESA(struct vn_cs_encoder *enc, VkCommandFlagsEXT cmd_flags, uint64_t ring, const VkRingCreateInfoMESA* pCreateInfo)
{
    const VkCommandTypeEXT cmd_type = VK_COMMAND_TYPE_vkCreateRingMESA_EXT;

    vn_encode_VkCommandTypeEXT(enc, &cmd_type);
    vn_encode_VkFlags(enc, &cmd_flags);

    vn_encode_uint64_t(enc, &ring);
    if (vn_encode_simple_pointer(enc, pCreateInfo))
        vn_encode_VkRingCreateInfoMESA(enc, pCreateInfo);
}

static inline size_t vn_sizeof_vkCreateRingMESA_reply(uint64_t ring, const VkRingCreateInfoMESA* pCreateInfo)
{
    const VkCommandTypeEXT cmd_type = VK_COMMAND_TYPE_vkCreateRingMESA_EXT;
    size_t cmd_size = vn_sizeof_VkCommandTypeEXT(&cmd_type);

    /* skip ring */
    /* skip pCreateInfo */

    return cmd_size;
}

static inline void vn_decode_vkCreateRingMESA_reply(struct vn_cs_decoder *dec, uint64_t ring, const VkRingCreateInfoMESA* pCreateInfo)
{
    VkCommandTypeEXT command_type;
    vn_decode_VkCommandTypeEXT(dec, &command_type);
    assert(command_type == VK_COMMAND_TYPE_vkCreateRingMESA_EXT);

    /* skip ring */
    /* skip pCreateInfo */
}

static inline size_t vn_sizeof_vkDestroyRingMESA(uint64_t ring)
{
    const VkCommandTypeEXT cmd_type = VK_COMMAND_TYPE_vkDestroyRingMESA_EXT;
    const VkFlags cmd_flags = 0;
    size_t cmd_size = vn_sizeof_VkCommandTypeEXT(&cmd_type) + vn_sizeof_VkFlags(&cmd_flags);

    cmd_size += vn_sizeof_uint64_t(&ring);

    return cmd_size;
}

static inline void vn_encode_vkDestroyRingMESA(struct vn_cs_encoder *enc, VkCommandFlagsEXT cmd_flags, uint64_t ring)
{
    const VkCommandTypeEXT cmd_type = VK_COMMAND_TYPE_vkDestroyRingMESA_EXT;

    vn_encode_VkCommandTypeEXT(enc, &cmd_type);
    vn_encode_VkFlags(enc, &cmd_flags);

    vn_encode_uint64_t(enc, &ring);
}

static inline size_t vn_sizeof_vkDestroyRingMESA_reply(uint64_t ring)
{
    const VkCommandTypeEXT cmd_type = VK_COMMAND_TYPE_vkDestroyRingMESA_EXT;
    size_t cmd_size = vn_sizeof_VkCommandTypeEXT(&cmd_type);

    /* skip ring */

    return cmd_size;
}

static inline void vn_decode_vkDestroyRingMESA_reply(struct vn_cs_decoder *dec, uint64_t ring)
{
    VkCommandTypeEXT command_type;
    vn_decode_VkCommandTypeEXT(dec, &command_type);
    assert(command_type == VK_COMMAND_TYPE_vkDestroyRingMESA_EXT);

    /* skip ring */
}

static inline size_t vn_sizeof_vkNotifyRingMESA(uint64_t ring, uint32_t seqno, VkRingNotifyFlagsMESA flags)
{
    const VkCommandTypeEXT cmd_type = VK_COMMAND_TYPE_vkNotifyRingMESA_EXT;
    const VkFlags cmd_flags = 0;
    size_t cmd_size = vn_sizeof_VkCommandTypeEXT(&cmd_type) + vn_sizeof_VkFlags(&cmd_flags);

    cmd_size += vn_sizeof_uint64_t(&ring);
    cmd_size += vn_sizeof_uint32_t(&seqno);
    cmd_size += vn_sizeof_VkFlags(&flags);

    return cmd_size;
}

static inline void vn_encode_vkNotifyRingMESA(struct vn_cs_encoder *enc, VkCommandFlagsEXT cmd_flags, uint64_t ring, uint32_t seqno, VkRingNotifyFlagsMESA flags)
{
    const VkCommandTypeEXT cmd_type = VK_COMMAND_TYPE_vkNotifyRingMESA_EXT;

    vn_encode_VkCommandTypeEXT(enc, &cmd_type);
    vn_encode_VkFlags(enc, &cmd_flags);

    vn_encode_uint64_t(enc, &ring);
    vn_encode_uint32_t(enc, &seqno);
    vn_encode_VkFlags(enc, &flags);
}

static inline size_t vn_sizeof_vkNotifyRingMESA_reply(uint64_t ring, uint32_t seqno, VkRingNotifyFlagsMESA flags)
{
    const VkCommandTypeEXT cmd_type = VK_COMMAND_TYPE_vkNotifyRingMESA_EXT;
    size_t cmd_size = vn_sizeof_VkCommandTypeEXT(&cmd_type);

    /* skip ring */
    /* skip seqno */
    /* skip flags */

    return cmd_size;
}

static inline void vn_decode_vkNotifyRingMESA_reply(struct vn_cs_decoder *dec, uint64_t ring, uint32_t seqno, VkRingNotifyFlagsMESA flags)
{
    VkCommandTypeEXT command_type;
    vn_decode_VkCommandTypeEXT(dec, &command_type);
    assert(command_type == VK_COMMAND_TYPE_vkNotifyRingMESA_EXT);

    /* skip ring */
    /* skip seqno */
    /* skip flags */
}

static inline size_t vn_sizeof_vkWriteRingExtraMESA(uint64_t ring, size_t offset, uint32_t value)
{
    const VkCommandTypeEXT cmd_type = VK_COMMAND_TYPE_vkWriteRingExtraMESA_EXT;
    const VkFlags cmd_flags = 0;
    size_t cmd_size = vn_sizeof_VkCommandTypeEXT(&cmd_type) + vn_sizeof_VkFlags(&cmd_flags);

    cmd_size += vn_sizeof_uint64_t(&ring);
    cmd_size += vn_sizeof_size_t(&offset);
    cmd_size += vn_sizeof_uint32_t(&value);

    return cmd_size;
}

static inline void vn_encode_vkWriteRingExtraMESA(struct vn_cs_encoder *enc, VkCommandFlagsEXT cmd_flags, uint64_t ring, size_t offset, uint32_t value)
{
    const VkCommandTypeEXT cmd_type = VK_COMMAND_TYPE_vkWriteRingExtraMESA_EXT;

    vn_encode_VkCommandTypeEXT(enc, &cmd_type);
    vn_encode_VkFlags(enc, &cmd_flags);

    vn_encode_uint64_t(enc, &ring);
    vn_encode_size_t(enc, &offset);
    vn_encode_uint32_t(enc, &value);
}

static inline size_t vn_sizeof_vkWriteRingExtraMESA_reply(uint64_t ring, size_t offset, uint32_t value)
{
    const VkCommandTypeEXT cmd_type = VK_COMMAND_TYPE_vkWriteRingExtraMESA_EXT;
    size_t cmd_size = vn_sizeof_VkCommandTypeEXT(&cmd_type);

    /* skip ring */
    /* skip offset */
    /* skip value */

    return cmd_size;
}

static inline void vn_decode_vkWriteRingExtraMESA_reply(struct vn_cs_decoder *dec, uint64_t ring, size_t offset, uint32_t value)
{
    VkCommandTypeEXT command_type;
    vn_decode_VkCommandTypeEXT(dec, &command_type);
    assert(command_type == VK_COMMAND_TYPE_vkWriteRingExtraMESA_EXT);

    /* skip ring */
    /* skip offset */
    /* skip value */
}

static inline size_t vn_sizeof_vkGetVenusExperimentalFeatureData100000MESA(size_t* pDataSize, void* pData)
{
    const VkCommandTypeEXT cmd_type = VK_COMMAND_TYPE_vkGetVenusExperimentalFeatureData100000MESA_EXT;
    const VkFlags cmd_flags = 0;
    size_t cmd_size = vn_sizeof_VkCommandTypeEXT(&cmd_type) + vn_sizeof_VkFlags(&cmd_flags);

    cmd_size += vn_sizeof_simple_pointer(pDataSize);
    if (pDataSize)
        cmd_size += vn_sizeof_size_t(pDataSize);
    cmd_size += vn_sizeof_simple_pointer(pData); /* out */

    return cmd_size;
}

static inline void vn_encode_vkGetVenusExperimentalFeatureData100000MESA(struct vn_cs_encoder *enc, VkCommandFlagsEXT cmd_flags, size_t* pDataSize, void* pData)
{
    const VkCommandTypeEXT cmd_type = VK_COMMAND_TYPE_vkGetVenusExperimentalFeatureData100000MESA_EXT;

    vn_encode_VkCommandTypeEXT(enc, &cmd_type);
    vn_encode_VkFlags(enc, &cmd_flags);

    if (vn_encode_simple_pointer(enc, pDataSize))
        vn_encode_size_t(enc, pDataSize);
    vn_encode_array_size(enc, pData ? (pDataSize ? *pDataSize : 0) : 0); /* out */
}

static inline size_t vn_sizeof_vkGetVenusExperimentalFeatureData100000MESA_reply(size_t* pDataSize, void* pData)
{
    const VkCommandTypeEXT cmd_type = VK_COMMAND_TYPE_vkGetVenusExperimentalFeatureData100000MESA_EXT;
    size_t cmd_size = vn_sizeof_VkCommandTypeEXT(&cmd_type);

    cmd_size += vn_sizeof_simple_pointer(pDataSize);
    if (pDataSize)
        cmd_size += vn_sizeof_size_t(pDataSize);
    if (pData) {
        cmd_size += vn_sizeof_array_size((pDataSize ? *pDataSize : 0));
        cmd_size += vn_sizeof_blob_array(pData, (pDataSize ? *pDataSize : 0));
    } else {
        cmd_size += vn_sizeof_array_size(0);
    }

    return cmd_size;
}

static inline void vn_decode_vkGetVenusExperimentalFeatureData100000MESA_reply(struct vn_cs_decoder *dec, size_t* pDataSize, void* pData)
{
    VkCommandTypeEXT command_type;
    vn_decode_VkCommandTypeEXT(dec, &command_type);
    assert(command_type == VK_COMMAND_TYPE_vkGetVenusExperimentalFeatureData100000MESA_EXT);

    if (vn_decode_simple_pointer(dec)) {
        vn_decode_size_t(dec, pDataSize);
    } else {
        pDataSize = NULL;
    }
    if (vn_peek_array_size(dec)) {
        const size_t array_size = vn_decode_array_size(dec, (pDataSize ? *pDataSize : 0));
        vn_decode_blob_array(dec, pData, array_size);
    } else {
        vn_decode_array_size_unchecked(dec);
        pData = NULL;
    }
}

static inline void vn_submit_vkSetReplyCommandStreamMESA(struct vn_instance *vn_instance, VkCommandFlagsEXT cmd_flags, const VkCommandStreamDescriptionMESA* pStream, struct vn_instance_submit_command *submit)
{
    uint8_t local_cmd_data[VN_SUBMIT_LOCAL_CMD_SIZE];
    void *cmd_data = local_cmd_data;
    size_t cmd_size = vn_sizeof_vkSetReplyCommandStreamMESA(pStream);
    if (cmd_size > sizeof(local_cmd_data)) {
        cmd_data = malloc(cmd_size);
        if (!cmd_data)
            cmd_size = 0;
    }
    const size_t reply_size = cmd_flags & VK_COMMAND_GENERATE_REPLY_BIT_EXT ? vn_sizeof_vkSetReplyCommandStreamMESA_reply(pStream) : 0;

    struct vn_cs_encoder *enc = vn_instance_submit_command_init(vn_instance, submit, cmd_data, cmd_size, reply_size);
    if (cmd_size) {
        vn_encode_vkSetReplyCommandStreamMESA(enc, cmd_flags, pStream);
        vn_instance_submit_command(vn_instance, submit);
        if (cmd_data != local_cmd_data)
            free(cmd_data);
    }
}

static inline void vn_submit_vkSeekReplyCommandStreamMESA(struct vn_instance *vn_instance, VkCommandFlagsEXT cmd_flags, size_t position, struct vn_instance_submit_command *submit)
{
    uint8_t local_cmd_data[VN_SUBMIT_LOCAL_CMD_SIZE];
    void *cmd_data = local_cmd_data;
    size_t cmd_size = vn_sizeof_vkSeekReplyCommandStreamMESA(position);
    if (cmd_size > sizeof(local_cmd_data)) {
        cmd_data = malloc(cmd_size);
        if (!cmd_data)
            cmd_size = 0;
    }
    const size_t reply_size = cmd_flags & VK_COMMAND_GENERATE_REPLY_BIT_EXT ? vn_sizeof_vkSeekReplyCommandStreamMESA_reply(position) : 0;

    struct vn_cs_encoder *enc = vn_instance_submit_command_init(vn_instance, submit, cmd_data, cmd_size, reply_size);
    if (cmd_size) {
        vn_encode_vkSeekReplyCommandStreamMESA(enc, cmd_flags, position);
        vn_instance_submit_command(vn_instance, submit);
        if (cmd_data != local_cmd_data)
            free(cmd_data);
    }
}

static inline void vn_submit_vkExecuteCommandStreamsMESA(struct vn_instance *vn_instance, VkCommandFlagsEXT cmd_flags, uint32_t streamCount, const VkCommandStreamDescriptionMESA* pStreams, const size_t* pReplyPositions, uint32_t dependencyCount, const VkCommandStreamDependencyMESA* pDependencies, VkCommandStreamExecutionFlagsMESA flags, struct vn_instance_submit_command *submit)
{
    uint8_t local_cmd_data[VN_SUBMIT_LOCAL_CMD_SIZE];
    void *cmd_data = local_cmd_data;
    size_t cmd_size = vn_sizeof_vkExecuteCommandStreamsMESA(streamCount, pStreams, pReplyPositions, dependencyCount, pDependencies, flags);
    if (cmd_size > sizeof(local_cmd_data)) {
        cmd_data = malloc(cmd_size);
        if (!cmd_data)
            cmd_size = 0;
    }
    const size_t reply_size = cmd_flags & VK_COMMAND_GENERATE_REPLY_BIT_EXT ? vn_sizeof_vkExecuteCommandStreamsMESA_reply(streamCount, pStreams, pReplyPositions, dependencyCount, pDependencies, flags) : 0;

    struct vn_cs_encoder *enc = vn_instance_submit_command_init(vn_instance, submit, cmd_data, cmd_size, reply_size);
    if (cmd_size) {
        vn_encode_vkExecuteCommandStreamsMESA(enc, cmd_flags, streamCount, pStreams, pReplyPositions, dependencyCount, pDependencies, flags);
        vn_instance_submit_command(vn_instance, submit);
        if (cmd_data != local_cmd_data)
            free(cmd_data);
    }
}

static inline void vn_submit_vkCreateRingMESA(struct vn_instance *vn_instance, VkCommandFlagsEXT cmd_flags, uint64_t ring, const VkRingCreateInfoMESA* pCreateInfo, struct vn_instance_submit_command *submit)
{
    uint8_t local_cmd_data[VN_SUBMIT_LOCAL_CMD_SIZE];
    void *cmd_data = local_cmd_data;
    size_t cmd_size = vn_sizeof_vkCreateRingMESA(ring, pCreateInfo);
    if (cmd_size > sizeof(local_cmd_data)) {
        cmd_data = malloc(cmd_size);
        if (!cmd_data)
            cmd_size = 0;
    }
    const size_t reply_size = cmd_flags & VK_COMMAND_GENERATE_REPLY_BIT_EXT ? vn_sizeof_vkCreateRingMESA_reply(ring, pCreateInfo) : 0;

    struct vn_cs_encoder *enc = vn_instance_submit_command_init(vn_instance, submit, cmd_data, cmd_size, reply_size);
    if (cmd_size) {
        vn_encode_vkCreateRingMESA(enc, cmd_flags, ring, pCreateInfo);
        vn_instance_submit_command(vn_instance, submit);
        if (cmd_data != local_cmd_data)
            free(cmd_data);
    }
}

static inline void vn_submit_vkDestroyRingMESA(struct vn_instance *vn_instance, VkCommandFlagsEXT cmd_flags, uint64_t ring, struct vn_instance_submit_command *submit)
{
    uint8_t local_cmd_data[VN_SUBMIT_LOCAL_CMD_SIZE];
    void *cmd_data = local_cmd_data;
    size_t cmd_size = vn_sizeof_vkDestroyRingMESA(ring);
    if (cmd_size > sizeof(local_cmd_data)) {
        cmd_data = malloc(cmd_size);
        if (!cmd_data)
            cmd_size = 0;
    }
    const size_t reply_size = cmd_flags & VK_COMMAND_GENERATE_REPLY_BIT_EXT ? vn_sizeof_vkDestroyRingMESA_reply(ring) : 0;

    struct vn_cs_encoder *enc = vn_instance_submit_command_init(vn_instance, submit, cmd_data, cmd_size, reply_size);
    if (cmd_size) {
        vn_encode_vkDestroyRingMESA(enc, cmd_flags, ring);
        vn_instance_submit_command(vn_instance, submit);
        if (cmd_data != local_cmd_data)
            free(cmd_data);
    }
}

static inline void vn_submit_vkNotifyRingMESA(struct vn_instance *vn_instance, VkCommandFlagsEXT cmd_flags, uint64_t ring, uint32_t seqno, VkRingNotifyFlagsMESA flags, struct vn_instance_submit_command *submit)
{
    uint8_t local_cmd_data[VN_SUBMIT_LOCAL_CMD_SIZE];
    void *cmd_data = local_cmd_data;
    size_t cmd_size = vn_sizeof_vkNotifyRingMESA(ring, seqno, flags);
    if (cmd_size > sizeof(local_cmd_data)) {
        cmd_data = malloc(cmd_size);
        if (!cmd_data)
            cmd_size = 0;
    }
    const size_t reply_size = cmd_flags & VK_COMMAND_GENERATE_REPLY_BIT_EXT ? vn_sizeof_vkNotifyRingMESA_reply(ring, seqno, flags) : 0;

    struct vn_cs_encoder *enc = vn_instance_submit_command_init(vn_instance, submit, cmd_data, cmd_size, reply_size);
    if (cmd_size) {
        vn_encode_vkNotifyRingMESA(enc, cmd_flags, ring, seqno, flags);
        vn_instance_submit_command(vn_instance, submit);
        if (cmd_data != local_cmd_data)
            free(cmd_data);
    }
}

static inline void vn_submit_vkWriteRingExtraMESA(struct vn_instance *vn_instance, VkCommandFlagsEXT cmd_flags, uint64_t ring, size_t offset, uint32_t value, struct vn_instance_submit_command *submit)
{
    uint8_t local_cmd_data[VN_SUBMIT_LOCAL_CMD_SIZE];
    void *cmd_data = local_cmd_data;
    size_t cmd_size = vn_sizeof_vkWriteRingExtraMESA(ring, offset, value);
    if (cmd_size > sizeof(local_cmd_data)) {
        cmd_data = malloc(cmd_size);
        if (!cmd_data)
            cmd_size = 0;
    }
    const size_t reply_size = cmd_flags & VK_COMMAND_GENERATE_REPLY_BIT_EXT ? vn_sizeof_vkWriteRingExtraMESA_reply(ring, offset, value) : 0;

    struct vn_cs_encoder *enc = vn_instance_submit_command_init(vn_instance, submit, cmd_data, cmd_size, reply_size);
    if (cmd_size) {
        vn_encode_vkWriteRingExtraMESA(enc, cmd_flags, ring, offset, value);
        vn_instance_submit_command(vn_instance, submit);
        if (cmd_data != local_cmd_data)
            free(cmd_data);
    }
}

static inline void vn_submit_vkGetVenusExperimentalFeatureData100000MESA(struct vn_instance *vn_instance, VkCommandFlagsEXT cmd_flags, size_t* pDataSize, void* pData, struct vn_instance_submit_command *submit)
{
    uint8_t local_cmd_data[VN_SUBMIT_LOCAL_CMD_SIZE];
    void *cmd_data = local_cmd_data;
    size_t cmd_size = vn_sizeof_vkGetVenusExperimentalFeatureData100000MESA(pDataSize, pData);
    if (cmd_size > sizeof(local_cmd_data)) {
        cmd_data = malloc(cmd_size);
        if (!cmd_data)
            cmd_size = 0;
    }
    const size_t reply_size = cmd_flags & VK_COMMAND_GENERATE_REPLY_BIT_EXT ? vn_sizeof_vkGetVenusExperimentalFeatureData100000MESA_reply(pDataSize, pData) : 0;

    struct vn_cs_encoder *enc = vn_instance_submit_command_init(vn_instance, submit, cmd_data, cmd_size, reply_size);
    if (cmd_size) {
        vn_encode_vkGetVenusExperimentalFeatureData100000MESA(enc, cmd_flags, pDataSize, pData);
        vn_instance_submit_command(vn_instance, submit);
        if (cmd_data != local_cmd_data)
            free(cmd_data);
    }
}

static inline void vn_call_vkSetReplyCommandStreamMESA(struct vn_instance *vn_instance, const VkCommandStreamDescriptionMESA* pStream)
{
    VN_TRACE_FUNC();

    struct vn_instance_submit_command submit;
    vn_submit_vkSetReplyCommandStreamMESA(vn_instance, VK_COMMAND_GENERATE_REPLY_BIT_EXT, pStream, &submit);
    struct vn_cs_decoder *dec = vn_instance_get_command_reply(vn_instance, &submit);
    if (dec) {
        vn_decode_vkSetReplyCommandStreamMESA_reply(dec, pStream);
        vn_instance_free_command_reply(vn_instance, &submit);
    }
}

static inline void vn_async_vkSetReplyCommandStreamMESA(struct vn_instance *vn_instance, const VkCommandStreamDescriptionMESA* pStream)
{
    struct vn_instance_submit_command submit;
    vn_submit_vkSetReplyCommandStreamMESA(vn_instance, 0, pStream, &submit);
}

static inline void vn_call_vkSeekReplyCommandStreamMESA(struct vn_instance *vn_instance, size_t position)
{
    VN_TRACE_FUNC();

    struct vn_instance_submit_command submit;
    vn_submit_vkSeekReplyCommandStreamMESA(vn_instance, VK_COMMAND_GENERATE_REPLY_BIT_EXT, position, &submit);
    struct vn_cs_decoder *dec = vn_instance_get_command_reply(vn_instance, &submit);
    if (dec) {
        vn_decode_vkSeekReplyCommandStreamMESA_reply(dec, position);
        vn_instance_free_command_reply(vn_instance, &submit);
    }
}

static inline void vn_async_vkSeekReplyCommandStreamMESA(struct vn_instance *vn_instance, size_t position)
{
    struct vn_instance_submit_command submit;
    vn_submit_vkSeekReplyCommandStreamMESA(vn_instance, 0, position, &submit);
}

static inline void vn_call_vkExecuteCommandStreamsMESA(struct vn_instance *vn_instance, uint32_t streamCount, const VkCommandStreamDescriptionMESA* pStreams, const size_t* pReplyPositions, uint32_t dependencyCount, const VkCommandStreamDependencyMESA* pDependencies, VkCommandStreamExecutionFlagsMESA flags)
{
    VN_TRACE_FUNC();

    struct vn_instance_submit_command submit;
    vn_submit_vkExecuteCommandStreamsMESA(vn_instance, VK_COMMAND_GENERATE_REPLY_BIT_EXT, streamCount, pStreams, pReplyPositions, dependencyCount, pDependencies, flags, &submit);
    struct vn_cs_decoder *dec = vn_instance_get_command_reply(vn_instance, &submit);
    if (dec) {
        vn_decode_vkExecuteCommandStreamsMESA_reply(dec, streamCount, pStreams, pReplyPositions, dependencyCount, pDependencies, flags);
        vn_instance_free_command_reply(vn_instance, &submit);
    }
}

static inline void vn_async_vkExecuteCommandStreamsMESA(struct vn_instance *vn_instance, uint32_t streamCount, const VkCommandStreamDescriptionMESA* pStreams, const size_t* pReplyPositions, uint32_t dependencyCount, const VkCommandStreamDependencyMESA* pDependencies, VkCommandStreamExecutionFlagsMESA flags)
{
    struct vn_instance_submit_command submit;
    vn_submit_vkExecuteCommandStreamsMESA(vn_instance, 0, streamCount, pStreams, pReplyPositions, dependencyCount, pDependencies, flags, &submit);
}

static inline void vn_call_vkCreateRingMESA(struct vn_instance *vn_instance, uint64_t ring, const VkRingCreateInfoMESA* pCreateInfo)
{
    VN_TRACE_FUNC();

    struct vn_instance_submit_command submit;
    vn_submit_vkCreateRingMESA(vn_instance, VK_COMMAND_GENERATE_REPLY_BIT_EXT, ring, pCreateInfo, &submit);
    struct vn_cs_decoder *dec = vn_instance_get_command_reply(vn_instance, &submit);
    if (dec) {
        vn_decode_vkCreateRingMESA_reply(dec, ring, pCreateInfo);
        vn_instance_free_command_reply(vn_instance, &submit);
    }
}

static inline void vn_async_vkCreateRingMESA(struct vn_instance *vn_instance, uint64_t ring, const VkRingCreateInfoMESA* pCreateInfo)
{
    struct vn_instance_submit_command submit;
    vn_submit_vkCreateRingMESA(vn_instance, 0, ring, pCreateInfo, &submit);
}

static inline void vn_call_vkDestroyRingMESA(struct vn_instance *vn_instance, uint64_t ring)
{
    VN_TRACE_FUNC();

    struct vn_instance_submit_command submit;
    vn_submit_vkDestroyRingMESA(vn_instance, VK_COMMAND_GENERATE_REPLY_BIT_EXT, ring, &submit);
    struct vn_cs_decoder *dec = vn_instance_get_command_reply(vn_instance, &submit);
    if (dec) {
        vn_decode_vkDestroyRingMESA_reply(dec, ring);
        vn_instance_free_command_reply(vn_instance, &submit);
    }
}

static inline void vn_async_vkDestroyRingMESA(struct vn_instance *vn_instance, uint64_t ring)
{
    struct vn_instance_submit_command submit;
    vn_submit_vkDestroyRingMESA(vn_instance, 0, ring, &submit);
}

static inline void vn_call_vkNotifyRingMESA(struct vn_instance *vn_instance, uint64_t ring, uint32_t seqno, VkRingNotifyFlagsMESA flags)
{
    VN_TRACE_FUNC();

    struct vn_instance_submit_command submit;
    vn_submit_vkNotifyRingMESA(vn_instance, VK_COMMAND_GENERATE_REPLY_BIT_EXT, ring, seqno, flags, &submit);
    struct vn_cs_decoder *dec = vn_instance_get_command_reply(vn_instance, &submit);
    if (dec) {
        vn_decode_vkNotifyRingMESA_reply(dec, ring, seqno, flags);
        vn_instance_free_command_reply(vn_instance, &submit);
    }
}

static inline void vn_async_vkNotifyRingMESA(struct vn_instance *vn_instance, uint64_t ring, uint32_t seqno, VkRingNotifyFlagsMESA flags)
{
    struct vn_instance_submit_command submit;
    vn_submit_vkNotifyRingMESA(vn_instance, 0, ring, seqno, flags, &submit);
}

static inline void vn_call_vkWriteRingExtraMESA(struct vn_instance *vn_instance, uint64_t ring, size_t offset, uint32_t value)
{
    VN_TRACE_FUNC();

    struct vn_instance_submit_command submit;
    vn_submit_vkWriteRingExtraMESA(vn_instance, VK_COMMAND_GENERATE_REPLY_BIT_EXT, ring, offset, value, &submit);
    struct vn_cs_decoder *dec = vn_instance_get_command_reply(vn_instance, &submit);
    if (dec) {
        vn_decode_vkWriteRingExtraMESA_reply(dec, ring, offset, value);
        vn_instance_free_command_reply(vn_instance, &submit);
    }
}

static inline void vn_async_vkWriteRingExtraMESA(struct vn_instance *vn_instance, uint64_t ring, size_t offset, uint32_t value)
{
    struct vn_instance_submit_command submit;
    vn_submit_vkWriteRingExtraMESA(vn_instance, 0, ring, offset, value, &submit);
}

static inline void vn_call_vkGetVenusExperimentalFeatureData100000MESA(struct vn_instance *vn_instance, size_t* pDataSize, void* pData)
{
    VN_TRACE_FUNC();

    struct vn_instance_submit_command submit;
    vn_submit_vkGetVenusExperimentalFeatureData100000MESA(vn_instance, VK_COMMAND_GENERATE_REPLY_BIT_EXT, pDataSize, pData, &submit);
    struct vn_cs_decoder *dec = vn_instance_get_command_reply(vn_instance, &submit);
    if (dec) {
        vn_decode_vkGetVenusExperimentalFeatureData100000MESA_reply(dec, pDataSize, pData);
        vn_instance_free_command_reply(vn_instance, &submit);
    }
}

static inline void vn_async_vkGetVenusExperimentalFeatureData100000MESA(struct vn_instance *vn_instance, size_t* pDataSize, void* pData)
{
    struct vn_instance_submit_command submit;
    vn_submit_vkGetVenusExperimentalFeatureData100000MESA(vn_instance, 0, pDataSize, pData, &submit);
}

#endif /* VN_PROTOCOL_DRIVER_TRANSPORT_H */
