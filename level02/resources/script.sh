#/bin/bash

i=1

while [ $i -le 32 ]
do
	echo $i
	echo "%$i\$p" | ./level02 | grep does
	i=$(( $i + 1 ))
done
