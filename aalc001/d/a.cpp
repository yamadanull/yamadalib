#include "../../template/template.hpp"
#include "../../segment-tree/segment-tree.hpp"
#include "../../monoid/generate-monoid.hpp"
using namespace yamada;

const int K=3;
using T=pr<ll,array<ll,K>>;
T F(T X,T Y){
	auto[ans,cnt]=X;
	auto[bns,dnt]=Y;

	ll cns=ans+bns;
	auto ent=cnt;
	FOR_E(e,d,Zip(ent,dnt))e+=d;

	FOR(i,K)FOR(j,i){
		cns+=cnt[i]*dnt[j];
	}
	return{cns,ent};
}
T ti(){
	return{0,array<ll,K>{}};
}
T genT(ll a){
	auto ans=ti();
	ans.se[a]=1;
	return ans;
}
using Mono=MyMonoid<T,F,ti>;

void yamada::solve()
{
	LL(N,Q);
	vl A(N); IN(A);
	SegmentTree<Mono> seg(A|Transform([](auto a)->T{ return genT(a); })|rtov);
	FOR(Q){
		LL(op);
		if(op==1){
			LL(i,x); --i;
			seg.set(i,genT(x));
		}
		else{
			LL(l,r); --l;
			OUT(seg(l,r).fi);
		}
	}
}
