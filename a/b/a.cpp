#include "../../template/multitest-template.hpp"

void yamada::solve()
{
	IN(N,A=LL*N);
	ll ans=infLL;
	each(a,A){
		ll bns=0;
		each(b,A)if(b%a)++bns;
		amin(ans,bns);
	}
	out(ans);
}
