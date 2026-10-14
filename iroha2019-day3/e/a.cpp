#include "../../template/template.hpp"

void yamada::solve()
{
	inl(N);
	V<bool> fn;
	rep(i,N){
		char c; in(c);
		fn.eb(!(c=='/'));
	}

	vp lr;
	for(ll l=0,r=0; l<N; l=r){
		while(r<N && fn[l]==fn[r])++r;
		lr.eb(l,r);
	}

	ll ans=0;
	rep(i,1,lr.size()){
		auto[l,r]=lr[i];
		if(fn[l]){
			auto[L,R]=lr[i-1];
			if(r-l==R-L)++ans;
		}
	}
	out(ans);
}
