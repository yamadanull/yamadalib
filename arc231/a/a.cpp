#include "../../template/multitest-template.hpp"

const int M=500;
void yamada::solve()
{
	inl(N);
	vv(ll,dp,M,M,infLL);
	ll offset=0;
	rep(j,M)dp[0][j]=j*j;
	rep(N){
		inl(I,J,C);
		offset+=C;
		ll bns=infLL;
		each(i,d,dp|enumerate)amin(bns,d[J]+(i-I)*(i-I)-C);
		if(amin(dp[I][J],bns)){
			rep(j,M)amin(dp[I][j],dp[I][J]+(j-J)*(j-J));
		}
	}
	ll ans=Min(dp|join)+offset;
	out(ans);
}
