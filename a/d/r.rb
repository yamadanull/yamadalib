p T=1000
T.times{
	p n=rand(1..5)
	puts a=(1..n).map{rand(0..5)}*' '
}
