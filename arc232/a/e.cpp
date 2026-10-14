#include "../../template/multitest-template.hpp"
using namespace yamada;

bool check(vp LR){
	Sort(LR);
	FOR_E(lr0,lr1,LR|Adjacent<2>){
		auto[l,r]=lr0;
		auto[L,R]=lr1;
		if(l==L)return 0;
		if(r>=R)return 0;
	}
	FOR_E(l,r,LR)if(r-l==1)return 0;
	return 1;
}
bool naive(ll N,vp lr){
	FOR(msk,1<<N){
		bool bns=1;
		FOR_E(l,r,lr){
			ll cnt=0;
			FOR(i,l,r)if(msk>>i&1)++cnt;
			if(cnt!=2)bns=0;
		}
		if(bns)return 1;
	}
	return 0;
}

void exper(){
	LL(N,M);
	vp lr(M);
	FOR_E(l,r,lr)IN(l,r),--l;
	if(!check(lr))return;
}

void yamada::solve()
{
	exper();
}
