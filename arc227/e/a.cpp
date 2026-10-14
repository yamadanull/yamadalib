#include "../../template/template.hpp"
#include "../../modint/montgomery-modint.hpp"
using namespace yamada;

using mint = LazyMontgomeryModInt<998244353>;
mint cal(vl A){ // to opt
	ll N=A.size();
	ll M=Sum(A);
	vv(mint,dp,N+1,M+1);
	dp[0][0]=1;
	rep(i,N)rep(j,M+1)if(dp[i][j]!=0){
		// 0
		dp[i+1][(j+A[i])/2]+=dp[i][j];
		// 1
		if(j+A[i]>0){
			dp[i+1][(j+A[i]-1)/2]+=dp[i][j];
		}
	}
	mint ans=0;
	each(d,dp[N])ans+=d;
	return ans;
}

void yamada::solve()
{
	inl(N,M);
	vl cnt(N);
	rep(M){
		inl(a);
		cnt[a]++;
	}

	mint ans=1;
	rep(i,1,N,2){
		vl dnt;
		for(ll j=i; j<N; j*=2){
			dnt.eb(cnt[j]);
		}
		ans*=cal(dnt);
	}
	out(ans);
}
