#include "../../template/multitest-template.hpp"

void yamada::solve()
{
	IN(N,Q);
	if(N==1)DIE(0);
	if(N%2)++N;
	auto get_mid=[&](ll L,ll R)->ll{
		if(popcnt(R-L)<=1)return (L+R)/2;
		ll d=R-L;
		d=1<<(msb(d)+1);
		return L+d/2;
	};
	vp ans;
	ans.eb(0,get_mid(0,N));
	[&](this auto dfs,ll L,ll M,ll R)->void{
		err(L,M,R);
		if(R-L<=2)return;
		ll m1=get_mid(L,M);
		ll m2=get_mid(M,R);
		ans.eb(m1,m2);
		dfs(L,m1,M);
		dfs(M,m2,R);
	}(0,get_mid(0,N),N);
	assert(len(ans)==ceil(N,2LL));
	out(len(ans));
	each(l,r,ans)out(l+1,r);
}
