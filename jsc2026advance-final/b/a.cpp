#include "../../template/template.hpp"

void yamada::solve()
{
	inl(N);
	const int DIV=10;
	bool ans=1;
	rep(L,0,N,DIV){
		ll R=min(N,L+DIV);
		rep(i,L,R){
			inl(a); --a;
			if(!inLR(L,a,R))ans=0;
		}
	}
	YesNo(ans);
}
