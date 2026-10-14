#include "../../template/template.hpp"

void yamada::solve()
{
	inl(N,M);
	vv(ll,fn,M,N);
	vl cnt(M);
	rep(i,N){
		inl(k); --k;
		fn[k][i]=1;
		cnt[k]++;
	}
	V<CumulativeSum<ll>> cum;
	each(f,fn)cum.eb(f);

	vl dp(1<<M,infLL);
	dp[0]=0;
	rep(msk,1<<M){
		/* out(msk,dp[msk]); */
		ll L=0;
		rep(k,M)if(msk>>k&1)L+=cnt[k];

		rep(k,M)if(!(msk>>k&1)){
			ll nsk=msk+(1<<k);
			ll R=L+cnt[k];
			ll add=R-L-cum[k].query(L,R);
			/* out(msk,nsk,":",L,R,add); */
			amin(dp[nsk],dp[msk]+add);
		}
	}

	out(dp.back());
}
