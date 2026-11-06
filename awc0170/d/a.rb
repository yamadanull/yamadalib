N,A=$<.map{_1.split.map &:to_i}
p N
p A
p A.sum{|x,y|
	cnt=[[0,0],[0,0]]
	A.map{|a,b|
		cnt[a-x&1][b-y&1]+=1
	}
	[0,1].sum{|x0|[0,1].sum{|x1|[0,1].sum{|y0|[0,1].sum{|y1|
		x0*y1+x1*y0&1 ? 0 : cnt[x0][y0]*cnt[x1][y1]
	}}}}
}
