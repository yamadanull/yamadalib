#include "../../template/multitest-template.hpp"

void yamada::solve()
{
	IN(N,K,A=LL*N);
	Sort(A);
	if(YESNO(K==N||A[N-K-1]<A.back())){
		vl ans(N);
		rep(i,K)ans[i]=A[i+N-K];
		rep(i,K,N)ans[i]=A[N-1-i];
		out(ans);
	}
}
