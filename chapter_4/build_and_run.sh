#!/bin/bash

set -e

CHAPTER="chapter_4"
PROJECT_ROOT="/workspaces/learn-mikanOS"
VM_ROOT="/workspaces/learn-mikanOS/mnt"
EDK2_DIR=${HOME}/edk2
OSBOOK_DIR=${HOME}/osbook
TARGET_CONFIG_FILE=${PROJECT_ROOT}/config/target.txt

# build kernel
source ${OSBOOK_DIR}/devenv/buildenv.sh
make

# create symbolic link in edk2 directory
ln -is ${PROJECT_ROOT}/${CHAPTER}/MikanLoaderPkg ${EDK2_DIR}

# copy target.txt to edk2 dir
cp -i ${TARGET_CONFIG_FILE} ${EDK2_DIR}/Conf/target.txt

# source edk
cd ${EDK2_DIR} 
source edksetup.sh

# build
build

# move efi to vm_root
cp -i ${EDK2_DIR}/Build/MikanLoaderX64/DEBUG_CLANG38/X64/Loader.efi ${VM_ROOT}/efi/boot/bootx64.efi

# move kernel to vm_root
cp -i ${PROJECT_ROOT}/${CHAPTER}/kernel/kernel.elf ${VM_ROOT}/kernel.elf

# run
${PROJECT_ROOT}/tools/run_qemu.sh ${VM_ROOT}
