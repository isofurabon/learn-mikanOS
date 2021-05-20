#!/bin/sh -l
# MIT License

# Copyright (c) 2021 Sarisia

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
set -e

# clone repos & setup build envs
# build EDK II
git clone --recursive https://github.com/tianocore/edk2.git ${HOME}/edk2 \
 && (cd ${HOME}/edk2 && git checkout 38c8be123aced4cc8ad5c7e0da9121a181b94251) \
 && make -C ${HOME}/edk2/BaseTools/Source/C
#  && rm -rf edk2

# clone mikanos devenv
git clone https://github.com/uchan-nos/mikanos-build.git ${HOME}/osbook

# download standard libraries
curl -L https://github.com/uchan-nos/mikanos-build/releases/download/v2.0/x86_64-elf.tar.gz \
  | tar xzvf - -C ${HOME}/osbook/devenv
  

# MIT License
#
# Copyright (c) 2021 isofurabon
#


# Build all
WORKSPACE_ROOT="${GITHUB_WORKSPACE:-/learn-mikanos}"
echo "Start Building..."

for chapter in $( ls -d ${WORKSPACE_ROOT}/*/ | grep chapter_.*/$ ); do   
    echo "\t"${chapter}...
    ${WORKSPACE_ROOT}/scripts/build.sh $(basename ${chapter})
done

echo "All Success!!"
