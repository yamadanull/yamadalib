#include "../../template/template.hpp"
#include "../../segment-tree/lazy-segment-tree-utility.hpp"

void yamada::solve()
{
	IN(N,M);
	auto[lr0,lr1]=[&]()->pair<vp,vp>{
		updatesum_lazyseg<ll> seg01(N-1);
		vp lr0,lr1;
		rep(M){
			IN(t,l=--LL,r);
			if(t)seg01.apply(l,r-1,1);
			else lr0.eb(l,r);
		}
		err();
		for(ll l=0,r=0; l<N-1; l=r){
			while(r<N-1 && seg01[l]==seg01[r])++r;
			if(seg01[l])lr1.eb(l,r+1);
		}
		err();
		return{lr0,lr1};
	}();
	err(lr0);
	err(lr1);

	updatesum_lazyseg<ll> seg(Iota(0,N)|Transform([&](auto i){return N-i;})|rtov);
	each(l,r,lr1){
		seg.apply(l,r,seg[l]);
	}
	bool ans=1;
	each(l,r,lr0){
		if(seg[l]==seg[r-1])ans=0;
	}
	if(YESNO(ans))out(seg.get());
}
