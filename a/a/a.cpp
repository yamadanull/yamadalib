#include "../../template/multitest-template.hpp"

void yamada::solve()
{
	IN(L,R);
	if(L*R>0)DIE(R-L);
	ll l=-L;
	ll r=R;
	if(l>r)swap(l,r);
	out(max<ll>(0,r-l-1));
}
