#!/bin/bash

set -ue
if [ $# -ne 1 ]; then
    echo "Usage: $0 FS_PATH" > /dev/stderr
    exit 
fi

FS_PATH=$1

qemu-system-x86_64 \
    -drive if=pflash,format=raw,readonly,file=${HOME}/osbook/devenv/OVMF_CODE.fd \
    -drive if=pflash,format=raw,file=${HOME}/osbook/devenv/OVMF_VARS.fd \
    -drive format=raw,file=fat:rw:${FS_PATH} \