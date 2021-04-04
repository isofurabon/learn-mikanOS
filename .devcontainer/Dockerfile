# See here for image contents: https://github.com/microsoft/vscode-dev-containers/tree/v0.166.0/containers/ubuntu/.devcontainer/base.Dockerfile

# [Choice] Ubuntu version: bionic, focal
ARG VARIANT="focal"
FROM mcr.microsoft.com/vscode/devcontainers/base:0-${VARIANT}

MAINTAINER isofurabon

# install packages
RUN apt-get update && export DEBIAN_FRONTEND=noninteractive && apt-get -y install --no-install-recommends git ansible dosfstools
USER vscode

# setup mikanos-build environment
RUN cd ~ && git clone https://github.com/uchan-nos/mikanos-build.git osbook
RUN cd ~/osbook/devenv && ansible-playbook -K -i ansible_inventory ansible_provision.yml 

