#include "../../template/template.hpp"
#include "../../graph/graph-template.hpp"
#include "../../dp/chmin-top2.hpp"

void yamada::solve()
{
	IN(N,M);
	auto g=wgraph<ll>(N,M,true);
	queue<ll> q;
	q.emplace(0);
	vp dp(N,mkp(infLL,infLL));
	dp[0]={0,-1};
	vp ep(N,mkp(infLL,infLL));
	while(!q.empty()){
		auto u=q.front(); q.pop();
		each(v,g[u]){
			if(dp[u].se!=v.cost && ChminTop2(dp[v],ep[v],mkp(dp[u].fi+1,v.cost))){
				q.emplace(v);
			}
			if(ep[u].se!=v.cost && ChminTop2(dp[v],ep[v],mkp(ep[u].fi+1,v.cost))){
				q.emplace(v);
			}
		}
	}
	ll ans=infLL;
	amin(ans,dp.back().fi);
	amin(ans,ep.back().fi);
	out(ans==infLL?-1:ans);
}
