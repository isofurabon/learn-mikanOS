#!/bin/bash

set -e

root_dir="/workspaces/learn-mikanOS"
work_dir=$(pwd)
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

# copy efi to here
cp Build/MikanLoaderX64/DEBUG_CLANG38/X64/Loader.efi ${work_dir}/bootx64.efi

# run
${root_dir}/tools/run_qemu.sh ${root_dir}/vm/fs

