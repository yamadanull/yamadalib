#include "../../template/template.hpp"

void yamada::solve()
{
	IN(N,A=--LL*N);
	ll M=7;
	vvl pos(M);
	rep(i,N)pos[A[i]].eb(i);
	VV(ll,nx,N,M,infLL);
	rep(i,N)rep(j,M){
		ll pi=lb(pos[j],i);
		if(pi==pos[j].size())continue;
		nx[i][j]=pos[j][pi];
	}

	ll ans=0;
	rep(l,N){
		ll rmin=Max(nx[l]);
		if(rmin<N)ans+=N-rmin;
	}
	out(ans);
}
