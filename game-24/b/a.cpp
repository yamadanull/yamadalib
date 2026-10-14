#include "../../template/template.hpp"

void yamada::solve()
{
	inl(H,W,N);
	ll l=infLL,r=-infLL,L=infLL,R=-infLL;
	rep(N){
		inl(a,b); --a; --b;
		amax(r,a);
		amax(R,b);
		amin(l,a);
		amin(L,b);
	}

	ll ans=0;
	ans^=l;
	ans^=H-r-1;
	ans^=L;
	ans^=W-R-1;
	out(ans?"Alice":"Bob");
}
