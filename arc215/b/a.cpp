#include "../../template/template.hpp"
#include "../../shortest-path/dijkstra.hpp"
#include "../../data-structure/union-find.hpp"
using namespace yamada;

void tc()
{
	inl(N); N*=2;
	vl A(N); in(A); each(a,A)--a;
	vvl pos(N/2);
	rep(i,N)pos[A[i]].eb(i);

	UnionFind uf(N);
	WeightedGraph<ll> g(N);
	each(ps,pos){
		ll u=ps[0],v=ps[1];
		uf.unite(u,v);
		g[u].eb(v,1);
		g[v].eb(u,1);
	}

	rep(i,N-1){
		ll u=i;
		ll v=i+1;
		if(uf.same(u,v))continue;
		g[u].eb(v,0);
		g[v].eb(u,0);
		uf.unite(u,v);
	}

	auto dp=dijkstra(g);
	vl ans;
	for(ll l=0,r=0; l<N; l=r){
		while(r<N && dp[l]%2==dp[r]%2)++r;
		if(r<N)ans.eb(r);
	}

	assert(ans.size()<=N/2);
	out(ans.size());
	out(ans);
}
void yamada::solve() { ini(T); while(T--)tc(); }
