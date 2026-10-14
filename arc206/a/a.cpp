#include "../../template/template.hpp"

void yamada::solve()
{
	inl(N);
	vl A(N); in(A); each(a,A)--a;

	vvp pos(N);
	for(ll l=0,r=0; l<N; l=r){
		while(r<N && A[l]==A[r])++r;
		pos[A[l]].eb(l,r);
	}

	ll ans=1;
	each(lr,pos)if(!lr.empty()){
		// ダブリ
		ll cnt=0;
		repr(i,lr.size()){
			auto[l,r]=lr[i];
			ans+=N-r-cnt;
			cnt+=r-l;
		}
	}
	out(ans);
}
