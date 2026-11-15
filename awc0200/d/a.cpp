#include "../../template/template.hpp"

void yamada::solve()
{
	IN(N,K,A=LL*N);
	ll ans=0;
	ll sm=Sum(A);
	rep(i,N){
		ans+=A[i]*(N-1)>=(i128)K*(sm-A[i]);
	}
	out(ans);
}
