p T=100
T.times{
	p n=rand(2..8)
	puts a=(n-1).times.map{rand(1.._1+1)}*' '
}
