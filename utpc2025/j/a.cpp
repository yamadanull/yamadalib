#include "../../template/template.hpp"

void yamada::solve()
{
	inl(N); N+=1;
	vl A{0};
	rep(i,N-1){
		inl(a,b);
		A.eb(a-b);
	}

	sort(all(A));
	ll ans=0;
	rep(i,N/2){
		ans+=-A[i]+A[N-i-1];
	}
	out(ans);
}
