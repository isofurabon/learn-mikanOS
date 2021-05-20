#!/bin/sh -l
set -e

# clone repos & setup build envs
# build EDK II
RUN git clone --recursive https://github.com/tianocore/edk2.git ${HOME}/edk2 \
 && (cd edk2 && git checkout 38c8be123aced4cc8ad5c7e0da9121a181b94251) \
 && make -C edk2/BaseTools/Source/C
#  && rm -rf edk2

# clone mikanos devenv
RUN git clone https://github.com/uchan-nos/mikanos-build.git ${HOME}/osbook

# download standard libraries
RUN curl -L https://github.com/uchan-nos/mikanos-build/releases/download/v2.0/x86_64-elf.tar.gz \
  | tar xzvf - -C ${HOME}/osbook/devenv

# Build all
WORKSPACE_ROOT="${GITHUB_WORKSPACE:-/learn-mikanos}"
echo "Start Building..."

for chapter in $( ls -d ${WORKSPACE_ROOT}/*/ | grep chapter_.*/$ ); do   
    echo "\t"${chapter}...
    ${WORKSPACE_ROOT}/scripts/build.sh $(basename ${chapter})
done

echo "All Success!!"