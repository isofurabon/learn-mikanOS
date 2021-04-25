FROM ghcr.io/sarisia/mikanos:latest

# change user to vscode for DISPLAY setting
USER vscode

# use edk2 with a specified verison.
# Please refer to https://github.com/uchan-nos/mikanos-build/issues/6
RUN cd ~/edk2 && git checkout "38c8be123aced4cc8ad5c7e0da9121a181b94251" && make -C ~/edk2/BaseTools/Source/C

# clone mikanos
RUN git clone https://github.com/uchan-nos/mikanos.git mikanos

# export display=:0 for wslg
ENV DISPLAY=:0