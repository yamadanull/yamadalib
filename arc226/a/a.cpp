#include "../../template/template.hpp"
#include "../../modulo/binomial.hpp"
#include "../../modint/montgomery-modint.hpp"

using mint = LazyMontgomeryModInt<998244353>;
Binomial<mint> binom;
void yamada::solve()
{
	inl(N); N*=2;
	vl cnt(N);
	rep(N/2){
		inl(l,r); --l; --r;
		cnt[l]++;
		cnt[r]--;
	}

	ll K=2;
	vv(mint,dp,N+1,K+1);
	dp[0][0]=1;
	rep(i,N)rep(j,K+1)if(dp[i][j]!=0){
		ll J=j+cnt[i];
		if(J<0 || J>K)continue;
		if(J<=j){ // 減らす
			dp[i+1][J]+=dp[i][j];
		}
		else{ // 増やす
			dp[i+1][J]+=dp[i][j]*binom(K-j,J-j);
		}
	}
	out(dp[N][0]);
}
