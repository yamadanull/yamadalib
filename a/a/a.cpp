#include "../../template/template.hpp"
#include "../../shortest-path/dijkstra.hpp"
#include "../../graph/graph-template.hpp"

void yamada::solve()
{
	IN(N,M,K,BC=PR(LL*N,LL)[M]);
	auto tomsk=[&](vl B)->ll{
		ll ans=0;
		each(i,b,B|Enumerate)ans+=b<<i;
		return ans;
	};
	set<ll>S;
	rep(K)S.insert(tomsk(LL[N]()));

	WeightedGraph<ll> g(1<<N);
	each(B,C,BC){
		ll msk=tomsk(B);
		rep(u,1<<N){
			ll v=u^msk;
			if(S.find(v)!=S.end())continue;
			g[u].eb(u^msk,C);
		}
	}
	out(dijkstra(g).back());
}
