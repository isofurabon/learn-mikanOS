#!/bin/bash

# debug mode (-x)
#set -uex
set -ue

if [ $# -ne 1 ]; then
        echo "Usage: $0 FILE" > /dev/stderr
        exit 1
fi

FILE=$1
od -A x -t x1 ${FILE}