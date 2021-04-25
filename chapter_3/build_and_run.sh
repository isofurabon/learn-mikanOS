#!/bin/bash

set -e

PROJECT_ROOT="/learn-mikanos"
VM_ROOT="${PROJECT_ROOT}/mnt"
EDK2_DIR="${HOME}/edk2"
TARGET_CONFIG_FILE="${PROJECT_ROOT}/config/target.txt"
OSBOOK_DIR=${HOME}/osbook

# build kernel
source ${OSBOOK_DIR}/devenv/buildenv.sh
clang++ ${CPPFLAGS} -O2 -Wall -g --target=x86_64-elf -ffreestanding -mno-red-zone -fno-exceptions -fno-rtti -std=c++17 -c kernel/main.cpp
ld.lld ${LDFLAGS} --entry KernelMain -z norelro --image-base 0x100000 --static -o kernel.elf main.o

# create symbolic link in edk2 directory
ln -fs ${PROJECT_ROOT}/chapter_3/MikanLoaderPkg ${EDK2_DIR}

# copy target.txt to edk2 dir
cp -f ${TARGET_CONFIG_FILE} ${EDK2_DIR}/Conf/target.txt

# source edk & build
(cd ${EDK2_DIR} && source edksetup.sh && build)

# move efi to vm_root
cp -f ${EDK2_DIR}/Build/MikanLoaderX64/DEBUG_CLANG38/X64/Loader.efi ${VM_ROOT}/efi/boot/bootx64.efi

# move kernel to vm_root
cp -f ${PROJECT_ROOT}/chapter_3/kernel.elf ${VM_ROOT}/kernel.elf

# run
${PROJECT_ROOT}/tools/run_qemu.sh ${VM_ROOT}
