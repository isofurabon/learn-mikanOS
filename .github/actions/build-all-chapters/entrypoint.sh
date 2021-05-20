#!/bin/sh -l
set -e

pwd
ls -al
echo $HOME
ls $HOME

WORKSPACE_ROOT="${GITHUB_WORKSPACE:-/learn-mikanos}"
echo "Start Building..."

for chapter in $( ls -d ${WORKSPACE_ROOT}/*/ | grep chapter_.*/$ ); do   
    echo "\t"${chapter}...
    ${WORKSPACE_ROOT}/scripts/build.sh $(basename ${chapter})
done

echo "All Success!!"