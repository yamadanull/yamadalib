#include "../../template/template.hpp"
#include "../../shortest-path/dijkstra.hpp"
#include "../../graph/graph-template.hpp"

void yamada::solve()
{
	IN(N,M,Q,A=LL*N);
	WeightedGraph<ll> g(N+1);
	rep(i,1,M+1){
		IN(u,v,w); --u; --v;
		g[u].eb(v,w<<i);
		g[v].eb(u,w<<i);
	}
	rep(u,N){
		g[u].eb(N,A[u]);
		g[N].eb(u,A[u]);
	}
	while(Q--){
		IN(st,go); --st; --go;
		out(dijkstra(g,st)[go]);
	}
}
