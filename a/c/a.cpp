#include "../../template/multitest-template.hpp"

void yamada::solve()
{
	IN(N,K,A=LL*N); --K;
	Sort(A);
	CumulativeSum cum(A);
	ll X=Isqrt(K);

	ll L=0;
	ll ans=infLL;
	rep(x,X+1){
		while(L<N-1&&A[L]<=x)++L;
		ll bns=cum(L,N-1)-x*(N-1-L);
		bns+=max(0LL,A.back()-(x==0?A.back():K/x));
		/* if(x<=5)err(x,bns); */
		amin(ans,bns);
	}
	out(ans);
}
