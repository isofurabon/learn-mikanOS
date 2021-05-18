#
# For Development
#
FROM ghcr.io/sarisia/mikanos:latest

# change user to vscode for DISPLAY setting
USER vscode

# clone mikanos
RUN git clone https://github.com/uchan-nos/mikanos.git mikanos

# export display=:0 for wslg
ENV DISPLAY=:0