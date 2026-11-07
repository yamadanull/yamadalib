eval"N,*A="+`dd`.split*?,
n=[0]*8
p (0...N).sum{|i|(1..7).map{|a|n[a]+=1 while n[a]<i||n[a]<N&&A[n[a]]!=a};N-n.max}
