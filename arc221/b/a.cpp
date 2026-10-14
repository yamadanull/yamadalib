#include "../../template/template.hpp"
#include "../../modulo/binomial.hpp"
#include "../../modint/arbitrary-modint.hpp"

using mint=ArbitraryModInt;
void yamada::solve()
{
	inl(N,MOD);
	mint::set_mod(MOD);
	Binomial<mint> binom;

	vv(mint,pw,N+1,N+1);
	rep(i,N+1)rep(j,N+1)pw[i][j]=((mint)i).pow(j);

	vv(mint,binom3,N+1,N+1);
	rep(n,1,N+1)rep(k,1,n+1){
		rep(i,1,k+1){
			if((k-i)%2==0)binom3[n][k]+=binom(k,i)*pw[i][n];
			else binom3[n][k]-=binom(k,i)*pw[i][n];
		}
	}

	vv(mint,binom9,N+1,N+1);
	rep(n,1,N+1)rep(k,1,n+1)binom9[n][k]=binom3[n][k]*binom.finv(k);

	// 残りiます、直前にjマス選んだ
	vv(mint,dp,N+1,N+1);
	dp[N][0]=1;
	// のこりNマス、JマスKグループ追加
	rep(J,1,N+1)rep(K,1,J+1){
		dp[N-J][J]+=binom(N,J)*binom9[J][K];
	}

	V<mint> pw2(N*N+1,1); rep(i,1,pw2.size())pw2[i]=pw2[i-1]*2;
	vv(mint,pw21,N+1,N+1); // (2^i-1)^j
	rep(i,N+1)rep(j,N+1)pw21[i][j]=(pw2[i]-1).pow(j);

	vv(mint,f,N+1,N+1);
	rep(j,N+1)rep(J,N+1){
		rep(K,1,J+1){
			f[j][J]+=binom9[J][K]*pw21[j][K];
		}
	}

	// のこりiマス, 直前にjマス選んだ、JマスKグループ追加
	repr(i,1,N)rep(K,1,i+1){
		mint bns=0;
		rep(j,1,N-i+1)if(dp[i][j]!=0){
			bns+=pw21[j][K]*pw2[(N-i-j)*K]*dp[i][j];
		}
		rep(J,K,i+1){
			dp[i-J][J]+=binom9[J][K]*binom(i,J)*bns;
		}
	}

	mint ans=0;
	each(ep,dp)each(d,ep)ans+=d;
	out(ans);
}
