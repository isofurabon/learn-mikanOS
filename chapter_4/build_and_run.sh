#!/bin/bash

set -e

CHAPTER="chapter_4"
PROJECT_ROOT="/workspaces/learn-mikanOS"
VM_ROOT="/workspaces/learn-mikanOS/mnt"
EDK2_DIR=${HOME}/edk2
OSBOOK_DIR=${HOME}/osbook
TARGET_CONFIG_FILE=../config/target.txt

# build kernel
source ${OSBOOK_DIR}/devenv/buildenv.sh
clang++ ${CPPFLAGS} -O2 -Wall -g --target=x86_64-elf -ffreestanding -mno-red-zone -fno-exceptions -fno-rtti -std=c++17 -c kernel/main.cpp
ld.lld ${LDFLAGS} --entry KernelMain -z norelro --image-base 0x100000 --static -o kernel.elf main.o

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
mv Build/MikanLoaderX64/DEBUG_CLANG38/X64/Loader.efi ${VM_ROOT}/efi/boot/bootx64.efi

# move kernel to vm_root
mv ${PROJECT_ROOT}/${CHAPTER}/kernel.elf ${VM_ROOT}/kernel.elf

# run
${PROJECT_ROOT}/tools/run_qemu.sh ${VM_ROOT}
