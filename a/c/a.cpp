#include "../../template/template.hpp"
#include "../../graph/graph-template.hpp"
#include "../../data-structure/union-find.hpp"

const int LG=62;
void yamada::solve()
{
	i128 N,M,Q; in(N,M,Q);
	vc<i128> A(N); in(A);
	UnionFind uf(N);
	vc<array<i128,3>> es;
	rep(i,M){
		i128 u,v,w; in(u,v,w); --u; --v; w*=2;
		if(w==0){
			uf.unite(u,v);
		}
		else if(i<LG){
			if(w<<i<1LL<<LG){
				es.pb({u,v,w<<i});
			}
		}
	}
	vc<i128> belong(N);
	auto grs=uf.groups();
	i128 G=len(grs);
	vc<i128> dp(G,infLL); // 超頂点までの距離
	rep(gi,G){
		each(u,grs[gi]){
			belong[u]=gi;
			amin(dp[gi],A[u]);
		}
	}
	WeightedGraph<i128> g(G);
	each(u,v,w,es){
		u=belong[u];
		v=belong[v];
		g[u].eb(v,w);
		g[v].eb(u,w);
	}
	{
		minpq<pair<i128,i128>> q;
		rep(gi,G)q.emplace(dp[gi],gi);
		while(!q.empty()){
			auto[d,u]=q.top(); q.pop();
			if(dp[u]!=d)continue;
			each(v,g[u]){
				if(amin(dp[v],d+v.cost)){
					q.emplace(dp[v],v);
				}
			}
		}
	}
	err(g);
	err(dp);
	while(Q--){
		IN(st,go); --st; --go;
		st=belong[st];
		go=belong[go];
		if(st==go){out(0);continue;}

		minpq<pair<i128,i128>> q;
		q.emplace(0,st);
		q.emplace(dp[st]+dp[go],go);
		map<i128,i128> ep;
		ep[go]=dp[st]+dp[go];
		ep[st]=0;

		while(!q.empty()){
			auto[d,u]=q.top(); q.pop();
			if(ep[u]!=d)continue;
			each(v,g[u]){
				if(!ep.count(v)||ep[v]>d+v.cost){
					q.emplace(ep[v]=d+v.cost,v);
				}
			}
		}
		err(ep);
		out(ep[go]);
	}
}
