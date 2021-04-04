# based on https://github.com/cupnes/introduction_to_x86_64_machine_language_samples/blob/master/tools/t2b
#!/bin/bash

# debug mode (-x)
#set -uex
set -ue

if [ $# -ne 1 ]; then
        echo "Usage: $0 FILE" > /dev/stderr
        exit 1
fi

FILE=$1

cut -d'#' -f1 ${FILE} | cut -d':' -f2 | tr ' ' '\n' | tr '\t' '\n' | grep -v '^$' | while read val; do
        printf "\x${val}"
done