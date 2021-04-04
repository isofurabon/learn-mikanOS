# based on https://github.com/cupnes/introduction_to_x86_64_machine_language_samples/blob/master/tools/run_qemu
#!/bin/bash
set -ue
if [ $# -ne 1 ]; then
    echo "Usage: $0 FS_PATH" > /dev/stderr
    exit 
fi

FS_PATH=$1

qemu-system-x86_64 \
    -drive if=pflash,format=raw,readonly,file=$HOME/osbook/devenv/OVMF_CODE.fd \
    -drive if=pflash,format=raw,file=$HOME/osbook/devenv/OVMF_VARS.fd \
    -drive dir=${FS_PATH},driver=vvfat,rw=on \
    -nographic
#    -vnc :0
#    -hda disk.img --nographics