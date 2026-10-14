#include "../../template/template.hpp"
#include "../../modulo/binomial.hpp"
#include "../../modint/montgomery-modint.hpp"

using mint = LazyMontgomeryModInt<998244353>;
Binomial<mint> binom;
void yamada::solve()
{
	inl(N,X);
	vl A(N); in(A);
	rep(i,N){
		X-=A[i]-i;
		amin(A[i],N-1);
	}
	sort(all(A));
	ll K=N*N;

	// i個のランプが未マッチング、損はj
	vv(mint,dp,N+1,K+1);
	dp[0][0]=1;
	rep(x,N){
		// x:時刻
		ll L=lb(A,x); // ランプの範囲
		ll R=ub(A,x);
		ll len=R-L;
		vv(mint,ep,N+1,K+1);

		rep(i,N+1)rep(j,K+1)if(dp[i][j]!=0){
			ll cnt=x-(L-i); // 過去の候補者数
			rep(k,min(len,cnt+1)+1){ // k個の範囲内ランプを片付ける
				// マッチング先が現在かどうかは関係なし
				/* out("A",i+len-k,j+i+len-k); cout.flush(); */
				ep[i+len-k][j+i+len-k]+=dp[i][j]*binom(len,k)*binom.P(cnt+1,k);
			}
			if(i>0)rep(k,min(len,cnt)+1){ // k個の範囲内ランプと過去、一個の範囲外ランプを現在
				/* out("B",i,j,len,k,":",i+len-k-1,j+i+len-k-1); cout.flush(); */
				ep[i+len-k-1][j+i+len-k-1]+=dp[i][j]*binom(len,k)*binom.P(cnt,k)*i;
			}
		}

		dp=ep;
	}
	/* out(dp[0]); */

	mint ans=0;
	rep(j,min(X,K)+1)ans+=dp[0][j];
	out(ans);
}
