#include "../../template/multitest-template.hpp"

void yamada::solve()
{
	inl(N);
	vl A(N),B(N); in2(A,B);
	vl C(N);
	rep(i,N){
		C[i]=A[i]-B[i];
	}
	ll bsm=Sum(B);
	ll amn=Min(A);

	sort(all(C));
	CumulativeSum cum(C);
	ll ans=infLL;
	rep(x,N+1){
		ll y=N-x;
		ll bns=bsm;
		bns+=cum(0,x);
		bns+=amn*max(0LL,y-x);
		amin(ans,bns);
	}
	out(ans);
}
