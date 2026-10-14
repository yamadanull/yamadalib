#include "../../template/template.hpp"

void yamada::solve()
{
	inl(N);
	vv(ll,A,4,N);
	in(A);
	each(a,A)sort(all(a));

	ll ans=infLL;
	each(v,A)each(a,v){
		ll bns=-infLL;
		rep(cls,4){
			ll L=lb(A[cls],a);
			if(L==N)bns=infLL;
			else{
				amax(bns,A[cls][L]-a);
			}
		}
		amin(ans,bns);
	}
	out(ans);
}
