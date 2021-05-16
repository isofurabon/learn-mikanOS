#!/bin/bash

set -e

PROJECT_ROOT="/learn-mikanos"
CHAPTER="chapter_6"
VM_ROOT="${PROJECT_ROOT}/mnt"
EDK2_DIR="${HOME}/edk2"
TARGET_CONFIG_FILE="${PROJECT_ROOT}/config/target.txt"
OSBOOK_DIR=${HOME}/osbook

# ln usb code
ln -fs ${PROJECT_ROOT}/common/usb ${PROJECT_ROOT}/${CHAPTER}/kernel/usb

# build kernel
(source ${OSBOOK_DIR}/devenv/buildenv.sh && make -C ${PROJECT_ROOT}/${CHAPTER}/kernel all)

# create symbolic link in edk2 directory
# use MikanLoaderPkg in chapter_4.
ln -fs ${PROJECT_ROOT}/chapter_4/MikanLoaderPkg ${EDK2_DIR}

# copy target.txt to edk2 dir
cp -f ${TARGET_CONFIG_FILE} ${EDK2_DIR}/Conf/target.txt

# source edk & build
rm -r ${EDK2_DIR}/Build/*
(cd ${EDK2_DIR} && source edksetup.sh && build)

# move efi to vm_root
cp -f ${EDK2_DIR}/Build/MikanLoaderX64/DEBUG_CLANG38/X64/Loader.efi ${VM_ROOT}/efi/boot/bootx64.efi

# move kernel to vm_root
cp -f ${PROJECT_ROOT}/${CHAPTER}/kernel/kernel.elf ${VM_ROOT}/kernel.elf

# run
${PROJECT_ROOT}/tools/run_qemu.sh ${VM_ROOT}
