require"ac-library-rb/priority_queue"
N,M,K=gets.split.map &:to_i
F=->a{(0...N).map{a[_1]<< _1}.sum}
BC=(1..M).map{a=gets.split.map &:to_i;[F[a[...N]],a[N]]}
S=Set.new $<.map{F[_1.split.map &:to_i]}

q=AcLibraryRb::HeapQueue.new([[0,0]]){_1[1]>_2[1]}
dp=[9e9]*(1<<N)
dp[0]=0
while !q.empty?
	u,d=q.pop
	next if dp[u]!=d
	BC.map{|b,c|
		v=u^b
		if d+c<dp[v] && !S.member?(v)
			dp[v]=d+c
			q<<[v,d+c]
		end
	}
end
o=dp[-1]
p o>1e9?-1:o
