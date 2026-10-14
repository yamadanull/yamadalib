#include "../../template/template.hpp"
#include "../../shortest-path/dijkstra.hpp"
#include "../../graph/graph-template.hpp"

void yamada::solve()
{
	inl(N,M);
	vl A(N); in(A);
	auto g=wgraph<ll>(N,M,1);

	ll ans=infLL;
	rep(u,N){
		auto dp=dijkstra(g,u);
		rep(v,N)if(v!=u){
			if(dp[v]>=0)amin(ans,dp[v]+A[u]+A[v]);
		}
	}
	ll bns=0;
	rep(u,N){
		auto dp=dijkstra(g,u);
		rep(v,N)if(v!=u){
			if(dp[v]>=0){
				if(dp[v]+A[u]+A[v]==ans)++bns;
			}
		}
	}
	out(ans,bns);
}
