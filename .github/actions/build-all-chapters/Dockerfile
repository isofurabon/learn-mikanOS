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

FROM mcr.microsoft.com/vscode/devcontainers/base:ubuntu-20.04

# install development tools
RUN apt-get update \
 && apt-get install -y --no-install-recommends \
    build-essential \
    llvm-7-dev \
    lld-7 \
    clang-7 \
    nasm \
    acpica-tools \
    uuid-dev \
    # qemu-system-x86 \
    # qemu-utils \
    xauth \
    unzip \
    # added
    # qemu-system-gui \
    # dosfstools \
    # git \
    python3-distutils \
 && apt-get clean -y \
 && rm -rf /var/lib/apt/lists

# set alternatives
RUN for item in \
        llvm-PerfectShuffle \
        llvm-ar \
        llvm-as \
        llvm-bcanalyzer \
        llvm-cat \
        llvm-cfi-verify \
        llvm-config \
        llvm-cov \
        llvm-c-test \
        llvm-cvtres \
        llvm-cxxdump \
        llvm-cxxfilt \
        llvm-diff \
        llvm-dis \
        llvm-dlltool \
        llvm-dwarfdump \
        llvm-dwp \
        llvm-exegesis \
        llvm-extract \
        llvm-lib \
        llvm-link \
        llvm-lto \
        llvm-lto2 \
        llvm-mc \
        llvm-mca \
        llvm-modextract \
        llvm-mt \
        llvm-nm \
        llvm-objcopy \
        llvm-objdump \
        llvm-opt-report \
        llvm-pdbutil \
        llvm-profdata \
        llvm-ranlib \
        llvm-rc \
        llvm-readelf \
        llvm-readobj \
        llvm-rtdyld \
        llvm-size \
        llvm-split \
        llvm-stress \
        llvm-strings \
        llvm-strip \
        llvm-symbolizer \
        llvm-tblgen \
        llvm-undname \
        llvm-xray \
        ld.lld \
        lld-link \
        clang \
        clang++ \
        clang-cpp \
    ; do \
        update-alternatives --install "/usr/bin/${item}" "${item}" "/usr/bin/${item}-7" 50 \
    ; done

# build EDK II
RUN git clone --recursive https://github.com/tianocore/edk2.git edk2 \
 && (cd edk2 && git checkout 38c8be123aced4cc8ad5c7e0da9121a181b94251) \
 && make -C edk2/BaseTools/Source/C
#  && rm -rf edk2

# clone mikanos devenv
RUN git clone https://github.com/uchan-nos/mikanos-build.git osbook

# download standard libraries
RUN curl -L https://github.com/uchan-nos/mikanos-build/releases/download/v2.0/x86_64-elf.tar.gz \
  | tar xzvf - -C osbook/devenv


COPY entrypoint.sh /entrypoint.sh

ENTRYPOINT ["/entrypoint.sh"]