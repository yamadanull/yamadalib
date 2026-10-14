#include "../../template/template.hpp"
#include "../../modint/montgomery-modint.hpp"

using mint = LazyMontgomeryModInt<998244353>;
void yamada::solve()
{
	inl(N);
	ll K=26;
	ins(S,T,U);

	vvvv(mint,dp,N+1,S.size(),T.size(),U.size());
	dp[0][0][0][0]=1;
	rep(i,N)rep(si,S.size())rep(ti,T.size())rep(ui,U.size()){
		rep(c,K){
			ll sI=si,tI=ti,uI=ui;
			if(c==S[si]-'a')++sI;
			if(c==T[ti]-'a')++tI;
			if(c==U[ui]-'a')++uI;
			if(sI>=S.size())continue;
			if(tI>=T.size())continue;
			if(uI>=U.size())continue;
			dp[i+1][sI][tI][uI]+=dp[i][si][ti][ui];
		}
	}
	mint ans=0;
	rep(a,S.size())rep(b,T.size())rep(c,U.size())ans+=dp[N][a][b][c];
	out(ans);
}
