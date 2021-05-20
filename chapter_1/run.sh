#!/bin/bash
set -e

WORKSPACE_ROOT="${GITHUB_WORKSPACE:-/learn-mikanos}"
VM_ROOT="${WORKSPACE_ROOT}/vm"


# copy efi to vm_root
rm -rf ${VM_ROOT}
mkdir -p ${VM_ROOT}/efi/boot
cp -f ./hello.efi ${VM_ROOT}/efi/boot/bootx64.efi

#run
${WORKSPACE_ROOT}/scripts/run_qemu.sh ${VM_ROOT}