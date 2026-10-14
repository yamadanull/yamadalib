cnt=0
while true; do
    ./r.out > inp
    ans1=$(./a.out < inp)
    ans2=$(./n.out < inp)
    cnt=$((cnt+1))
    if [ "$ans1" != "$ans2" ]; then
        echo "Wrong Answer on case $cnt"
        echo "a.out:"
        echo "$ans1"
        echo "n.out:"
        echo "$ans2"
        break
    else
        echo "Case $cnt OK"
    fi
done
