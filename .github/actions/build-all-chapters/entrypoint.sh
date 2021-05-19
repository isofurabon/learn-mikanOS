#!/bin/sh -l
set -e

WORKSPACE="${GITHUB_WORKSPACE:-/learn-mikanos}"
echo "Start Building..."

for chapter in $( ls -d ${WORKSPACE}/*/ | grep chapter_.*/$ ); do   
    echo -n "\t"${chapter}...
    ${WORKSPACE}/scripts/build.sh $(basename ${chapter})
done

echo "Complete!!"