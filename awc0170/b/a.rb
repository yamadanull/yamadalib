N=gets.to_i
A=gets.split.map(&:to_i).sort.reverse
H,M=A.sum.divmod(N)
p (0...N).sum{|i|((i<M ? H+1 : H)-A[i]).abs}/2
