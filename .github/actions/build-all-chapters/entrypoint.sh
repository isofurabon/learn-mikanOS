#!/bin/sh -l
for chapter in $( ls -d ${GITHUB_WORKSPACE}*/ | grep chapter_.*/$ ); do   
    echo ${chapter}
done