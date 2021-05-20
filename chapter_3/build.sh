#!/bin/bash
set -e

WORKSPACE_ROOT="${GITHUB_WORKSPACE:-/learn-mikanos}"
VM_ROOT="${WORKSPACE_ROOT}/vm"
EDK2_DIR="${HOME}/edk2"
OSBOOK_DIR=${HOME}/osbook

# clean
rm -f *.o *.elf *.efi

# build kernel
(source ${OSBOOK_DIR}/devenv/buildenv.sh && \
clang++ ${CPPFLAGS} -O2 -Wall -g --target=x86_64-elf -ffreestanding -mno-red-zone -fno-exceptions -fno-rtti -std=c++17 -c kernel/main.cpp && \
ld.lld ${LDFLAGS} --entry KernelMain -z norelro --image-base 0x100000 --static -o kernel.elf main.o)

# create symbolic link in edk2 directory
ln -fs $(realpath ./MikanLoaderPkg) ${EDK2_DIR}

# copy target.txt to edk2 dir
cp -f ./MikanLoaderPkg/target.txt ${EDK2_DIR}/Conf/target.txt

# source edk & build
rm -fr ${EDK2_DIR}/Build/*
(cd ${EDK2_DIR} && source edksetup.sh && build)