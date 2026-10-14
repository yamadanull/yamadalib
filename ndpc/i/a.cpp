#include "../../template/template.hpp"
#include "../../modulo/binomial.hpp"
#include "../../modint/montgomery-modint.hpp"

using mint = LazyMontgomeryModInt<998244353>;
Binomial<mint> binom;
void yamada::solve()
{
	inl(N,X,Y);
	vl cnt(N);
	rep(N){
		inl(a); --a;
		++cnt[a];
	}

	ll siz=0;
	vv(mint,dp,N+1,N+1);
	dp[0][0]=1;
	repr(i,N){
		if(cnt[i]==0)continue;
		vv(mint,ep,N+1,N+1);

		rep(l,N+1)rep(r,N+1)if(dp[l][r]!=0){
			if(siz==0){
				ep[l+1][r+1]+=dp[l][r];
				continue;
			}

			// cnt[i]>=2
			// LR
			ep[l+1][r+1]+=dp[l][r]*binom(siz+cnt[i]-2,cnt[i]-2);
			// L
			ep[l+1][r]+=dp[l][r]*binom(siz+cnt[i]-2,cnt[i]-1);
			// R
			ep[l][r+1]+=dp[l][r]*binom(siz+cnt[i]-2,cnt[i]-1);
			// none
			ep[l][r]+=dp[l][r]*binom(siz+cnt[i]-2,cnt[i]);
		}
		siz+=cnt[i];
		dp=ep;
	}
	out(dp[X][Y]);
}
