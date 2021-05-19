#!/bin/bash

# To debug, add an option "-x"
set -uex

if [ $# -ne 1 ]; then
        echo "Usage: $0 chapter_[1~30]" > /dev/stderr
        exit 1
fi

CHAPTER=$1
WORKSPACE_ROOT="${GITHUB_WORKSPACE:-/learn-mikanos}"

$(cd ${WORKSPACE_ROOT}/${CHAPTER} && ./build.sh)

echo "Build Complete!!"