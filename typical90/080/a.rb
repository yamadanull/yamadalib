eval"N,D,*A="+`dd`.split*?,
o=[1]+[0]*(1<<N)
D.times{|t|x=1;b=A.sum{_1[t]*x*=2}/2;o[b|x-=1]+=o[x]while x>0}
p o[-2]
