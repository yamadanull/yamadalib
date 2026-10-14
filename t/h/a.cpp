#include "../../template/template.hpp"
#include "../../graph/graph-template.hpp"
using namespace yamada;

void tc()
{
	inl(N);
	auto g=graph(N);
	ll root=-1;
	repr(u,N)if(g[u].size()>=2)root=u;
	vl dp(N);
	auto dfs=[&](auto&& dfs,ll u,ll p)->void{
		each(v,g[u])if(v!=p){
			dfs(dfs,v,u);
			dp[u]+=dp[v];
		}
		if(dp[u]==0)dp[u]=1;
	}; dfs(dfs,root,-1);

	each(d,dp)d%=2;
	ll ans=Sum(dp);
	if(dp[root]==0)die(ans);

	// 上にある(dp==1)のsum
	auto ep=dp;
	// 上にある(dp==0)のsum
	auto fp=ep; each(f,fp)f=1-f;
	auto efs=[&](auto&& efs,ll u,ll p)->void{
		if(p>=0)ep[u]+=ep[p];
		if(p>=0)fp[u]+=fp[p];
		each(v,g[u])if(v!=p){
			efs(efs,v,u);
		}
	}; efs(efs,root,-1);

	ll bns=infLL;
	rep(u,N)if(g[u].size()==1){
		amin(bns,ans+fp[u]-ep[u]);
	}
	out(bns);
}
void yamada::solve() { inl(T); while(T--)tc(); }
