eval"N,*A="+`dd`.split*?,
S=A.sum
M=1<<19
dp=[true]+[false]*M
A.map{|a|
	(M-1).downto(a).map{|i|
		dp[i]=true if dp[i-a]
	}
}

o=M
(0...M).map{|i|o=[o,(S-i*2).abs].min if dp[i]}
p o
