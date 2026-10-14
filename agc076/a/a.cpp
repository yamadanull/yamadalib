#include "../../template/template.hpp"
#include "../../modulo/binomial.hpp"
#include "../../modint/montgomery-modint.hpp"

using mint = LazyMontgomeryModInt<998244353>;
Binomial<mint> binom;
void yamada::solve()
{
	inl(N);
	if(N==1)die(1);

	// かぶりsizmax:i
	V<mint> memo;
	{
		// size:i かぶりsizmax:j
		vv(mint,dp,N+1,N+1);
		dp[0][0]=1;
		rep(x,N){
			vv(mint,ep,N+1,N+1);
			rep(i,N+1)rep(j,i+1)if(dp[i][j]!=0){
				// i個にk個を挿入
				rep(k,N-i+1){
					ll I=i+k;
					ll J=max(j,k);
					ep[I][J]+=dp[i][j]*binom(i+k,k);
				}
			}
			dp=ep;
		}
		memo=dp[N];
	}

	// 添字使用i、かぶりサイズj
	vv(mint,dp,N,N*2);
	dp[0][0]=1;
	rep(c,N*N){
		auto ep=dp;
		each(v,ep)each(a,v)a*=binom.fac(N);

		rep(i,N)rep(j,N*2){
			// この列のかぶりサイズmaxをkにする
			rep(k,2,N+1){
				ll I=i+1;
				ll J=j+k;
				if(I<N && J<N*2)ep[I][J]+=dp[i][j]*memo[k];
			}
		}
		dp=ep;
	}

	mint ans=0;
	rep(i,N)rep(j,N*2)if(-i+j<N)ans+=dp[i][j];
	out(ans);
}
