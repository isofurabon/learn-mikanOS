#!/bin/bash

set -e

PROJECT_ROOT="/learn-mikanos"
VM_ROOT="${PROJECT_ROOT}/mnt"
EDK2_DIR="${HOME}/edk2"
TARGET_CONFIG_FILE="${PROJECT_ROOT}/config/target.txt"

# create symbolic link in edk2 directory
ln -fs ${PROJECT_ROOT}/chapter_2/MikanLoaderPkg ${EDK2_DIR}

# copy target.txt to edk2 dir
cp -f ${TARGET_CONFIG_FILE} ${EDK2_DIR}/Conf/target.txt

# source edk & build
rm -fr ${EDK2_DIR}/Build/*
(cd ${EDK2_DIR} && source edksetup.sh && build)

# copy efi to vm_root
cp ${EDK2_DIR}/Build/MikanLoaderX64/DEBUG_CLANG38/X64/Loader.efi ${VM_ROOT}/efi/boot/bootx64.efi

# run
${PROJECT_ROOT}/tools/run_qemu.sh ${VM_ROOT}

