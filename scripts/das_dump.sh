#!/bin/bash

# for debug
# set -uex
set -ue

if [ $# -gt 0 ]; then
        if [ "$1" = "-f" ]; then
                objdump -D -b binary -m i386:x86-64 $2
        else
                work_dir=$(mktemp -d)
                for b in $@; do
                        printf "\x${b}" >>${work_dir}/a.bin
                done
                objdump -D -b binary -M intel -m i386:x86-64 ${work_dir}/a.bin
                rm -r ${work_dir}
        fi
else
        work_dir=$(mktemp -d)
        while read b; do
                printf "\x${b}" >>${work_dir}/a.bin
        done
        objdump -D -b binary -M intel -m i386:x86-64 ${work_dir}/a.bin
        rm -r ${work_dir}
fi