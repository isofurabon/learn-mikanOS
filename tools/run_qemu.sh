#!/bin/bash
set -ue
qemu-system-x86_64 \
    -drive if=pflash,format=raw,readonly,file=$HOME/osbook/devenv/OVMF_CODE.fd \
    -drive if=pflash,format=raw,file=$HOME/osbook/devenv/OVMF_VARS.fd \
    -drive dir=fs,driver=vvfat,rw=on \
    -nographic
#    -hda disk.img --nographics