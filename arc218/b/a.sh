#!/bin/bash

g++ -std=gnu++20 -O2 a.cpp -o a.out || { echo "a.cpp コンパイル失敗"; return 1; }
echo "a.cpp コンパイル成功"
g++ -std=gnu++20 -O2 n.cpp -o n.out || { echo "n.cpp コンパイル失敗"; return 1; }
echo "n.cpp コンパイル成功"
g++ -std=gnu++20 -O2 r.cpp -o r.out || { echo "r.cpp コンパイル失敗"; return 1; }
echo "r.cpp コンパイル成功"

cnt=0
while true; do
    ./r.out > inp
    ans1=$(./a.out < inp)
    ans2=$(./n.out < inp)
    cnt=$((cnt+1))
    if [ "$ans1" != "$ans2" ]; then
        echo "Wrong Answer on case $cnt"
        echo "===== input (inp) ====="
        lines=$(wc -l < inp)
        if [ "$lines" -le 20 ]; then
            cat inp
        else
            head -n 20 inp
            echo "..."
        fi
        echo "======================="
        echo "a.out:"
        echo "$ans1"
        echo "n.out:"
        echo "$ans2"
        break
    else
        echo "Case $cnt OK"
    fi
done

