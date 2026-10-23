#include "../../template/multitest-template.hpp"
#include "../../tree/tree-query.hpp"
#include "../../graph/graph-template.hpp"
using namespace yamada;

UnweightedGraph input_g(ll N){
	IN(S=STR);
	vl Rs(N,-1);
	{
		vl stk;
		each(i,c,S|Enumerate){
			if(c=='(')stk.eb(i);
			else{
				ll j=stk.back(); stk.pop_back();
				Rs[j]=i;
			}
		}
	}
	UnweightedGraph g(N/2+1);
	ll curu=0;
	[&](this auto dfs,ll u,ll L,ll R)->void{
		if(L+1==R)return;
		for(ll l=L+1,r=L+1; l<R; l=r+1){
			r=Rs[l];
			g[u].eb(curu);
			dfs(curu++,l,r);
		}
	}(curu++,-1,N);
	return g;
}

const int LG=18;
void yamada::solve()
{
	IN(N,K);
	auto g=input_g(N);
	N=len(g);
 
	Tree tree(g);
 
	VV(ll,dp,LG,N,infLL); // 1<<tのぼるコスト
	rep(u,N){
		ll cnt=0;
		each(v,g[u]){
			dp[0][v]=cnt;
			cnt+=tree.size(v);
		}
	}
	rep(t,1,LG)rep(u,N){
		ll m=tree.kth_ancestor(u,1<<(t-1));
		if(m<0)continue;
		amin(dp[t][u],dp[t-1][u]+dp[t-1][m]);
	}
 
	ll ans=0;
	rep(U,N){
		ll cnt=0;
		ll u=U;
		repr(t,LG){
			if(cnt+dp[t][u]>K)continue;
			cnt+=dp[t][u];
			u=tree.kth_ancestor(u,1<<t);
		}
		err(u,U);
		if(u>0)amax(ans,tree.len(U,u)+1);
		else{
			ll bns=tree.depth(U)+min(K,N-tree.depth(U)-1);
			amax(ans,bns);
		}
	}
	out(ans);
}

