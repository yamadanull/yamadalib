#include "../../template/template.hpp"

void yamada::solve()
{
	IN(N,M);
	vvl vals(M+1);
	ll freeval=0;
	rep(N){
		IN(c,v);
		vals[c].eb(v);
		freeval+=v;
	}
	vl ans(M+1);
	VV(ll,dp,N+1,M+1,-infLL); // i個選んでj円
	dp[0][0]=0;
	ll curM=M;
	repr(m,M+1)if(m==0 || !vals[m].empty()){
		{
			ll bns=-infLL;
			rep(i,N+1){
				ll R=max(0LL,M-(curM-m)*i+1);
				rep(j,R){
					amax(bns,dp[i][j]);
				}
			}
			rep(m2,m+1,curM+1){
				rep(i,N+1){
					ll L=max(0LL,M-(curM-m2+1)*i+1);
					ll R=max(0LL,M-(curM-m2)*i+1);
					rep(j,L,R)amax(bns,dp[i][j]);
				}
				ans[m2]=bns+freeval;
			}
		}

		VV(ll,ep,N+1,M+1,-infLL);
		rep(i,N+1)rep(j,M+1)if(dp[i][j]>=0){ // m+1円引き -> m円引き
			if(j+i*(curM-m)<=M)amax(ep[i][j+i*(curM-m)],dp[i][j]);
		}
		each(v,vals[m]){
			freeval-=v;
			repr(i,N)rep(j,M+1)if(ep[i][j]>=0){
				amax(ep[i+1][j],ep[i][j]+v);
			}
		}
		dp=ep;
		curM=m;
	}
	ans[0]=Max(dp|Join);
	each(a,ans)out(a);
}
