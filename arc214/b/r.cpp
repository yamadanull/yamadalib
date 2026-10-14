#include "../../template/template.hpp"
#include "../../misc/random-graph.hpp"
#include "../../misc/all.hpp"

void yamada::solve()
{
	ll N=randint(2,6);
	ll M=randint(0,5);
	WeightedGraph<ll> g(N);
	vl A(N+1); rep(i,N+1)A[i]=i;
	randshf(A);
	rep(M){
		ll u=-1,v=-1;
		while(u==v){
			u=randint(0,N);
			v=randint(0,N);
		}
		g[u].eb(v,A[u]^A[v]);
		g[v].eb(u,A[u]^A[v]);
	}

	print_graph(g);
}
