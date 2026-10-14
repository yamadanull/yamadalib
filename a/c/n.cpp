#include "../../template/template.hpp"

void yamada::solve()
{
	const int M=20;
	LL(N);
	vp xy(N);
	FOR_E(x,y,xy){
		IN(x,y);
		x*=2;
		y*=2;
	}

	ll ans=infLL;
	FOR(X,-M,M+1)FOR(Y,-M,M+1)FOR(X2,-M,M+1)FOR(Y2,-M,M+1){
		ll bns=-infLL;
		FOR_E(x,y,xy){
			ll d=infLL;
			amin(d,abs(x-X)+abs(y-Y));
			amin(d,abs(x-X2)+abs(y-Y2));
			amax(bns,d);
		}
		amin(ans,bns);
	}
	OUT(ans);
}
