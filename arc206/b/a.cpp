#include "../../template/template.hpp"

void yamada::solve()
{
	inl(N);
	vl A(N),C(N); in(A,C);
	each(a,A)--a; each(c,C)--c;

	vvl P(N);
	rep(i,N)P[C[i]].eb(A[i]);

	ll ans=0;
	rep(c,N)if(!P[c].empty()){
		vl dp;
		each(p,P[c]){
			ll pos=lb(dp,p);
			if(pos==dp.size())dp.eb(p);
			else dp[pos]=p;
		}
		ll cnt=P[c].size()-dp.size();
		ans+=(c+1)*cnt;
	}
	out(ans);
}
