#!/bin/bash

set -ex

VKD3D_PROTON_COMMIT="5b73139f182d86cd58a757e4b5f0d4cfad96d319"

VKD3D_PROTON_DST_DIR="/vkd3d-proton-tests"
VKD3D_PROTON_SRC_DIR="/vkd3d-proton-src"
VKD3D_PROTON_BUILD_DIR="/vkd3d-proton-$VKD3D_PROTON_VERSION"

function build_arch {
  local arch="$1"
  shift

  meson "$@"                               \
        -Denable_tests=true                \
        --buildtype release                \
        --prefix "$VKD3D_PROTON_DST_DIR"   \
        --strip                            \
        --bindir "x${arch}"                \
        --libdir "x${arch}"                \
        "$VKD3D_PROTON_BUILD_DIR/build.${arch}"

  ninja -C "$VKD3D_PROTON_BUILD_DIR/build.${arch}" install

  install -D -m755 -t "${VKD3D_PROTON_DST_DIR}/x${arch}/bin" "$VKD3D_PROTON_BUILD_DIR/build.${arch}/tests/d3d12"
}

git clone https://github.com/HansKristian-Work/vkd3d-proton.git --single-branch -b master --no-checkout "$VKD3D_PROTON_SRC_DIR"
pushd "$VKD3D_PROTON_SRC_DIR"
git checkout "$VKD3D_PROTON_COMMIT"
git submodule update --init --recursive
git submodule update --recursive
build_arch 64
build_arch 86
popd

rm -rf "$VKD3D_PROTON_BUILD_DIR"
rm -rf "$VKD3D_PROTON_SRC_DIR"
