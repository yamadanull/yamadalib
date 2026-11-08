#include "../../template/multitest-template.hpp"
#include "../../graph/graph-template.hpp"
#include "../../shortest-path/bfs.hpp"

void yamada::solve()
{
	IN(N,M,W,X,Y,Z); --W; --X; --Y; --Z;
	auto g=graph(N,M);
	UnweightedGraph G(N*N);
	auto idx=[&](ll U,ll u)->ll{return U*N+u;};

	rep(u,N)each(v,g[u]){
		rep(i,N)G[idx(i,u)].eb(idx(i,v));
		G[idx(u,v)].eb(idx(v,u));
	}
	auto dp=bfs(G,idx(W,X));
	out(dp[idx(Y,Z)]);
}
