#include "../../template/multitest-template.hpp"
#include "../../modint/montgomery-modint.hpp"
#include "../../graph/graph-template.hpp"

using mint = LazyMontgomeryModInt<998244353>;
void yamada::solve()
{
	IN(N);
	auto g=graph(N);
	IN(S=STR,T=STR);
	each(c,S)c-='0';
	each(c,T)c-='0';
	vl memo(N,-1);
	bool ans=1;
	[&](this auto dfs,ll u,ll p=-1,ll dep=0,bool kuri=false)->void{
		{
			ll m=S[u]^T[u]^kuri;
			if(memo[dep]>=0 && m^memo[dep])ans=0;
			memo[dep]=m;
		}
		kuri=(!T[u]&&kuri || (!T[u]||kuri)&&S[u]);
		err(u,p,kuri);
		each(v,g[u])if(v!=p){
			dfs(v,u,dep+1,kuri);
		}
	}(0);
	if(!ans)DIE(-1);
	err(memo);

	mint cof=1;
	mint bns=0;
	each(c,memo){
		if(c<0)break;
		bns+=cof*c;
		cof*=2;
	}
	out(bns);
}
