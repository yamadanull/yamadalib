#!/bin/bash

g++ -std=gnu++23 -O2 a.cpp -o a.out || { echo "a.cpp コンパイル失敗"; return 1; }
echo "a.cpp コンパイル成功"
g++ -std=gnu++23 -O2 r.cpp -o r.out || { echo "r.cpp コンパイル失敗"; return 1; }
echo "r.cpp コンパイル成功"

cnt=0
while true; do
	./r.out > inp
	./a.out < inp > /dev/null 2>&1
	if [ $? -ne 0 ]; then
		echo "Runtime Error on case $cnt"

		echo "===== input (inp) ====="
		lines=$(wc -l < inp)
		if [ "$lines" -le 20 ]; then
			cat inp
		else
			head -n 20 inp
			echo "..."
		fi
		echo "======================="

		break
	fi
	cnt=$((cnt+1))
	echo "Case $cnt OK"
done

