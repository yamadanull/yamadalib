#include "../../template/template.hpp"
#include "../../modint/montgomery-modint.hpp"
using namespace yamada;

using mint = LazyMontgomeryModInt<998244353>;
mint cal(ll N,ll R,vl A,vl B){
	ll sum=Sum(B)-Sum(A);
	auto Arui=mkrui(A);
	auto Brui=mkrui(B);

	vv(bool,fn,N+1,N+1);
	rep(i,N+1)rep(j,i+1){
		ll val=Brui[j]-Arui[i];
		ll las=sum-val;
		fn[i][j]=(las<R);
	}

	vv(mint,dp,N+1,N+1);
	dp[0][0]=1;
	rep(i,N+1)rep(j,N+1)if(fn[i][j]){
		if(i>0)dp[i][j]+=dp[i-1][j];
		if(j>0)dp[i][j]+=dp[i][j-1];
	}
	return dp[N][N];
}

void yamada::solve()
{
	inl(N,L,R); ++R;
	vl A(N),B(N); in(A,B);
	out(cal(N,R,A,B)-cal(N,L,A,B));
}
