while true; do
	./r.out > inp
	ans1=$(./a.out < inp)
	ans2=$(./n.out < inp)
	if [ "$ans1" != "$ans2" ]; then
		echo "Wrong Answer"
		echo "$ans1"
		echo "$ans2"
		break
	fi
done
