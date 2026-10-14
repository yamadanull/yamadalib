#include "../../template/template.hpp"
#include "../../prime/fast-factorize.hpp"
#include "../../modint/montgomery-modint.hpp"

using mint = LazyMontgomeryModInt<998244353>;
void yamada::solve()
{
	inl(N);
	vl A(N); in(A);
	vv(ll,cnt,N,N);
	rep(i,N)rep(j,i+1,N){
		cnt[i][j]=A[i]*A[j]/__gcd(A[i],A[j]);
	}

	V<mint> dp(N);
	dp[0]=1;
	rep(i,N-1){
		rep(I,i+1,N)dp[I]+=dp[i]*cnt[i][I];
	}
	rep(i,1,N)out(dp[i]);
}
