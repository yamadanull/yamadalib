(N,),C,P,A=$<.map{_1.split.map &:to_i}
f=A.tally
p (1..N).sum{f[1+u=N-_1]?C[u]+f[P[u-1]]=0:0}
