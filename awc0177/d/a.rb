(N,M,),*A=$<.map{_1.split.map &:to_i}
k=N*=M
p A.sort.reverse.sum{k-=a=[_2,-~N/2,k].min;_1*a}
