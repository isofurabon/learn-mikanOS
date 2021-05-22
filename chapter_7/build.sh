#!/bin/bash
set -e

WORKSPACE_ROOT="${GITHUB_WORKSPACE:-/learn-mikanos}"
VM_ROOT="${WORKSPACE_ROOT}/vm"
EDK2_DIR="${HOME}/edk2"
OSBOOK_DIR=${HOME}/osbook

# ln usb code
ln -fs ${WORKSPACE_ROOT}/common/usb ./kernel/usb

# rebuild kernel
(source ${OSBOOK_DIR}/devenv/buildenv.sh && make -C ./kernel clean && make -C ./kernel all)

# create symbolic link in edk2 directory
ln -fs $(realpath ../chapter_4/MikanLoaderPkg) ${EDK2_DIR}

# copy target.txt to edk2 dir
cp -f ../chapter_4/MikanLoaderPkg/target.txt ${EDK2_DIR}/Conf/target.txt

# source edk & build
rm -fr ${EDK2_DIR}/Build/*
(cd ${EDK2_DIR} && source edksetup.sh && build)