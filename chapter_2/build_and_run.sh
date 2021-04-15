#!/bin/bash

set -e

vm_root="/workspaces/learn-mikanOS/mnt"
root_dir="/workspaces/learn-mikanOS"
edk2_dir=${HOME}/edk2
target_config_file=../config/target.txt

# create symbolic link in edk2 directory
ln -is ${root_dir}/chapter_2/MikanLoaderPkg ${edk2_dir}

# copy target.txt to edk2 dir
cp -i ${target_config_file} ${edk2_dir}/Conf/target.txt

# source edk
cd ${edk2_dir} 
source edksetup.sh

# build
build

# copy efi to vm_root
cp Build/MikanLoaderX64/DEBUG_CLANG38/X64/Loader.efi ${vm_root}/efi/boot/bootx64.efi

# run
${root_dir}/tools/run_qemu.sh ${vm_root}

