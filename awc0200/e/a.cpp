#include "../../template/template.hpp"

void yamada::solve()
{
	IN(N,M,A=LL*N,PN=PR(LL,LL)[M]);
	err(A);
	auto I=mkiota(M);
	Sort(I,[&](ll i,ll j){return PN[i].fi!=PN[j].fi?PN[i]>PN[j]:i<j;});
	Sort(A,greater{});

	ll ai=0;
	vl ans(M);
	each(i,I){
		auto[p,n]=PN[i];
		err(p,n);
		ll aj=ai+n;
		if(aj>N)DIE(-1);
		rep(k,ai,aj)ans[i]+=A[k];
		ai=aj;
	}
	each(a,ans)out(a);
}
