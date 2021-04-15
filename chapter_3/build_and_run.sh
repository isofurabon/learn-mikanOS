#!/bin/bash

set -e

vm_root="/workspaces/learn-mikanOS/mnt"
root_dir="/workspaces/learn-mikanOS"
edk2_dir=${HOME}/edk2
target_config_file=../config/target.txt

# build kernel
clang++ -O2 -Wall -g --target=x86_64-elf -ffreestanding -mno-red-zone -fno-exceptions -fno-rtti -std=c++17 -c kernel/main.cpp
ld.lld --entry KernelMain -z norelro --image-base 0x100000 --static -o kernel.elf main.o

# create symbolic link in edk2 directory
ln -is ${root_dir}/chapter_3/MikanLoaderPkg ${edk2_dir}

# copy target.txt to edk2 dir
cp -i ${target_config_file} ${edk2_dir}/Conf/target.txt

# source edk
cd ${edk2_dir} 
source edksetup.sh

# build
build

# move efi to vm_root
mv Build/MikanLoaderX64/DEBUG_CLANG38/X64/Loader.efi ${vm_root}/efi/boot/bootx64.efi

# move kernel to vm_root
mv ${root_dir}/chapter_3/kernel.elf ${vm_root}/kernel.elf

# run
${root_dir}/tools/run_qemu.sh ${vm_root}
