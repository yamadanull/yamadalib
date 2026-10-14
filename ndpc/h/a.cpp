#include "../../template/template.hpp"

void yamada::solve()
{
	inl(N);
	vs S(N); in(S);
	vv(ll,dp,N,N,infLL);
	vv(ll,ep,N,N,-infLL);
	dp[0][0]=ep[0][0]=0;
	rep(i,N)rep(j,N){
		if(i>0){
			amin(dp[i][j],dp[i-1][j]+(S[i][j]=='@'));
			amax(ep[i][j],ep[i-1][j]+(S[i][j]=='@'));
		}
		if(j>0){
			amin(dp[i][j],dp[i][j-1]+(S[i][j]=='@'));
			amax(ep[i][j],ep[i][j-1]+(S[i][j]=='@'));
		}
	}

	vl imos(N*2-1);
	rep(i,N)rep(j,N){
		ll L=dp[i][j];
		ll R=ep[i][j]+1;
		if(inLR<ll>(0,L,imos.size()))++imos[L];
		if(inLR<ll>(0,R,imos.size()))--imos[R];
	}
	rep(i,1,imos.size())imos[i]+=imos[i-1];
	each(a,imos)out(a);
}
