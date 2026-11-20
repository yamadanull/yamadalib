puts T=1000
T.times{
	puts n=rand(8..20)
	puts k=rand(1..n)
	puts a=n.times.map{rand(1..10)}*' '
}
