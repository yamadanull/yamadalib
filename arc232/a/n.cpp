#include "../../template/multitest-template.hpp"
#include "../../segment-tree/lazy-segment-tree-utility.hpp"
using namespace yamada;

bool naive(ll N,vp LR){
	FOR(msk,1<<N){
		bool bns=1;
		FOR_E(l,r,LR){
			ll cnt=0;
			FOR(i,l,r)if(msk>>i&1)++cnt;
			if(cnt!=2)bns=0;
		}
		if(bns)return 1;
	}
	return 0;
}
/* bool cal(ll N,vp LR){ */
/* 	updatemax_lazyseg<ll> seg(vl(N,0)); // 1ならば使ってはいけない */
/* 	minpq<ll> qRL; */
/* 	minpq<pl> qL_R; // (l,-r) */
/* 	FOR_E(l,r,LR){ */
/* 		qRL.emplace(r,l); */
/* 		qL_R.emplace(l,-r); */
/* 	} */

/* 	while(!qL_R.empty()){ */
/* 		auto[L,R]=qL_R.top(); R*=-1; qL_R.pop(); */
/* 		vp lr; */
/* 		while(!qRL.empty()){ */
/* 			auto[r,l]=qRL.top(); qRL.pop(); */
/* 			if(r>R)break; */
/* 			lr.eb(l,r); */
/* 		} */

/* 		FOR_E(l,r,lr)amax(L,l),amin(R,r); */
/* 	} */
/* } */

void yamada::solve()
{
	LL(N,M);
	vp LR(M);
	FOR_E(l,r,LR)IN(l,r),--l;
	YesNo(naive(N,LR));
}
