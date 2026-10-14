#include "../../template/template.hpp"
#include "../../modint/montgomery-modint.hpp"
using namespace yamada;

using mint = LazyMontgomeryModInt<998244353>;
mint f0(VV<mint> A){
	ll N=A.size();
	auto dp=A;
	mint ans=0;
	rep(i,N)rep(j,N){
		if(i>0)dp[i][j]+=dp[i-1][j];
		if(j>0)dp[i][j]+=dp[i][j-1];
		if(A[i][j]==1)ans+=dp[i][j]-1;
	}
	return ans;
}

mint f1(VV<mint> A){
	each(v,A)each(a,v)a=(mint)1-a;
	return f0(A);
}

void yamada::solve()
{
	inl(N);
	if(N==2){
		out("01\n01");
		return;
	}

	vv(mint,ans,N,N);
	rep(i,N)rep(j,N){
		if(i-j==-1);
		else if(i-j==-(N-1));
		else if(i-j<=0)ans[i][j]=1;
	}
	mint a=f0(ans);
	mint b=f1(ans);
	assert(a==b);
	vs S(N);
	rep(i,N)rep(j,N)S[i]+=(ans[i][j]==0? '.':'#');
	each(s,S)out(s);
}
