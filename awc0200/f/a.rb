(N,M),A,*I=$<.map{_1.split.map &:to_i}
d=[f=-1e18]*M+[0]
A.zip(I<<[0,0]).map{|a,(b,c)|e=[f]*-~M;0.upto(M){|j|j<a||(e[k=[j-a+b,M].min]=[e[k],d[j]].max
e[k=j-a]=[e[k],d[j]+c].max)};d=e}
p d.max
