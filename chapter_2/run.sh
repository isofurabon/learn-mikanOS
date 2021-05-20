#!/bin/bash
set -e

WORKSPACE_ROOT="${GITHUB_WORKSPACE:-/learn-mikanos}"
VM_ROOT="${WORKSPACE_ROOT}/vm"
EDK2_DIR="${HOME}/edk2"

# copy efi to vm_root
mkdir -p ${VM_ROOT}/efi/boot
cp -f ${EDK2_DIR}/Build/MikanLoaderX64/DEBUG_CLANG38/X64/Loader.efi ${VM_ROOT}/efi/boot/bootx64.efi

#run
${WORKSPACE_ROOT}/scripts/run_qemu.sh ${VM_ROOT}
