#include "../../template/template.hpp"

void yamada::solve()
{
	inl(N);
	vl A(N); in(A);
	ll d=N/2+1;
	ll ans=infLL;
	rep(i,N/2){
		amin(ans,A[i+d]-A[i]);
	}
	out(ans);
}
