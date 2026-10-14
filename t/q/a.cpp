#include "../../template/template.hpp"
#include "../../modint/montgomery-modint.hpp"

void yamada::solve()
{
	using mint = LazyMontgomeryModInt<1000000007>;

	inl(N,L);
	ll M=8;
	VV<bool>W(M+1);
	rep(i,M+1)W[i].resize(1<<i,false);

	rep(i,N){
		ins(w);
		ll ans=0;
		rep(i,w.size())if(w[i]=='1')ans+=1<<i;
		W[w.size()][ans]=true;
	}

	vvv(mint,dp,L+1,1<<M,1<<M);
	dp[0][0][1]=1;
	rep(i,L)rep(j,PW(M))rep(k,PW(M))if(dp[i][j][k]!=0){
		{ // put 0
			ll J=(j*2)%PW(M);
			ll K=(k*2)%PW(M);
			rep(siz,M)if(k>>siz&1){
				ll s=(j&MSK(siz))*2;
				if(W[siz+1][s]){ K++; break; }
			}
			dp[i+1][J][K]+=dp[i][j][k];
		}
		{ // put 1
			ll J=(j*2)%PW(M)+1;
			ll K=(k*2)%PW(M);
			rep(siz,M)if(k>>siz&1){
				ll s=(j&MSK(siz))*2+1;
				if(W[siz+1][s]){ K++; break; }
			}
			dp[i+1][J][K]+=dp[i][j][k];
		}
	}

	mint ans=0;
	rep(j,PW(M))rep(k,1,PW(M),2)if(dp[L][j][k]!=0){
		ans+=dp[L][j][k];
	}
	out(ans);
}
