#!/bin/bash

g++ -std=gnu++20 -O2 a.cpp -o a.out || { echo "a.cpp コンパイル失敗"; return 1; }
echo "a.cpp コンパイル成功"
g++ -std=gnu++20 -O2 r.cpp -o r.out || { echo "r.cpp コンパイル失敗"; return 1; }
echo "r.cpp コンパイル成功"

cnt=0

while true; do
	echo "Start case $cnt"

	rm -f fifo_a fifo_r
	mkfifo fifo_a fifo_r

	# ダミーで両方開いてブロック防止
	exec 3<>fifo_a
	exec 4<>fifo_r

	./a.out < fifo_r > fifo_a 2> a.err &
	pid_a=$!
	./r.out < fifo_a > fifo_r 2> r.err &
	pid_r=$!

	wait $pid_a
	status_a=$?
	wait $pid_r
	status_r=$?

	exec 3>&-
	exec 4>&-
	if [ $status_a -ne 0 ] || [ $status_r -ne 0 ]; then
		echo "Error on case $cnt"
		echo "a.out status: $status_a"
		echo "r.out status: $status_r"

		echo "===== a.out stderr ====="
		cat a.err
		echo "===== r.out stderr ====="
		cat r.err

		break
	fi

	cnt=$((cnt+1))
	echo "Case $cnt OK"
done
