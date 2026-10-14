#include "../../template/template.hpp"
#include "../../flow/primal-dual.hpp"

void yamada::solve()
{
	IN(N,M,K,C,D);
	const int T=101;
	MinCostFlow<ll,ll> g;
	vvc<int> U; // [t,u]
	rep(t,T)U.eb(g.add_vertices(N));
	auto go=g.add_vertex();

	g.add_dem(go,K);
	rep(K)g.add_sup(U[0][(--LL)()],1);

	rep(t,T-1)rep(u,1,N)g.add_edge(U[t][u],U[t+1][u],infLL,0);
	rep(t,1,T)g.add_edge(U[t][0],go,infLL,C*t);
	rep(M){
		IN(u=--LL,v=--LL);
		rep(2){
			swap(u,v);
			rep(t,T-1)rep(cnt,1,K+1){
				ll cost=(cnt*2-1)*D;
				g.add_edge(U[t][u],U[t+1][v],1,cost);
			}
		}
	}

	out(g.solve().se);
}
