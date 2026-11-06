require"ac-library-rb/priority_queue"
Dijk=->g{
	n=g.size
	dp=[0]+[1e18]*(n-1)
	q=AcLibraryRb::PriorityQueue.new([0]){|x,y|x<y}
	while !q.empty?
		d,u=q.pop.divmod(n)
		next if dp[u]!=d
		g[u].map{|v,w|
			if dp[v]>dp[u]+w
				dp[v]=d+w
				q<<(d+w)*n+v
			end
		}
	end
	dp[-1]>1e17 ? -1 : dp[-1]
}

N,M=gets.split.map &:to_i
UVW=M.times.map{gets.split.map &:to_i}
gets
fn=[true]*M
gets.split.map{fn[_1.to_i-1]=false}

g=Array.new(N){[]}
h=Array.new(N){[]}
M.times{|ei|
	u,v,w=UVW[ei]
	u-=1;v-=1
	g[u]<<[v,w];g[v]<<[u,w]
	(h[u]<<[v,w];h[v]<<[u,w])if fn[ei]
}

p Dijk[g],Dijk[h]
