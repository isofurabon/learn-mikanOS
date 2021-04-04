# based on https://github.com/cupnes/introduction_to_x86_64_machine_language_samples/blob/master/tools/as_dump
#!/bin/bash

# set -uex
set -ue

work_dir=$(mktemp -d)

if [ $# -gt 0 ]; then
	if [ "$1" = "-f" ]; then
		as -mmnemonic=intel -mnaked-reg -msyntax=intel -o ${work_dir}/a.out $2
	else
		echo $@ | as -mmnemonic=intel -mnaked-reg -msyntax=intel -o ${work_dir}/a.out
	fi
else
	as -mmnemonic=intel -mnaked-reg -msyntax=intel -o ${work_dir}/a.out
fi

objdump -d -M intel ${work_dir}/a.out
rm -r ${work_dir}