p T=1000
T.times{
	p n=500
	p l=1<<30
	puts a=n.times.map{rand(1..1<<30)}*' '
}
