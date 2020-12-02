#!/bin/zsh

for i in {1..100}
do
	./generator > input
	time ./main < input > answer
	time ./main.py < input > output
	diff -w answer output
	if [ $? -ne 0 ];then;
		echo "error detected. process terminated."
		exit
	fi
	echo "testcase $i passed!"
done

rm -f input answer output
