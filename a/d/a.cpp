#include "../../template/multitest-template.hpp"
#include "../../shortest-path/bfs01.hpp"
#include "../../shortest-path/bfs.hpp"
#include "../../graph/graph-template.hpp"

void yamada::solve()
{
	IN(N,M,W,X,Y,Z); --W; --X; --Y; --Z;
	auto g=graph(N,M);
	rep(u,N)Sort(g[u]);
	if(W==Y)DIE(bfs(g,X)[Z]);

	WeightedGraph<ll> G(N*3+M*2);
	vp es;
	rep(u,N)each(v,g[u])es.eb(u,v);
	auto us0=mkiota(N);
	auto us1=us0; each(u,us1)u+=N;
	auto us2=us1; each(u,us2)u+=N;
	auto us3=[&](ll u,ll v)->ll{
		return lb<pl>(es,mkp(u,v))+N*3;
	};
	rep(u,N)each(v,g[u]){ // 00,11,23,33
		G[us0[u]].eb(us0[v],1);
		G[us1[u]].eb(us1[v],1);
		G[us3(u,v)].eb(us3(v,u),1);
		G[us2[u]].eb(us3(u,v),1);
		G[us3(u,v)].eb(us2[u],1);
	}
	each(v,g[W]){ // 03
		G[us0[v]].eb(us3(W,v),0); // Wv
		G[us3(W,v)].eb(us0[v],0);
	}
	each(v,g[Y]){ // 13
		G[us1[v]].eb(us3(Y,v),0); // Yv
		G[us3(Y,v)].eb(us1[v],0);
	}
	rep(u,len(G))err(u,G[u]);

	auto dp=bfs01(G,us0[X]);
	out(dp[us1[Z]]);
}
