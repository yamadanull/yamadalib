#include "../../template/template.hpp"
#include "../../segment-tree/lazy-segment-tree.hpp"
#include "../../monoid/generate-monoid.hpp"
#include "../../segment-tree/lazy-segment-tree-utility.hpp"
using namespace yamada;

using T=array<ll,2>;
using E=ll;
T ti(){return T{};}
E ei(){return E{};}
T F(T X,T Y){return {X[0]+Y[0],X[1]+Y[1]};}
T G(T X,E f,ll){if(f%2)swap(X[0],X[1]); return X;}
E H(E f,E g){return f+g;}
using AM=MyActedMonoid<T,E,F,G,H,ti,ei>;

void yamada::solve()
{
	LL(Q);
	vc<array<ll,3>> ques(Q); IN(ques);
	vl cmp;
	FOR_E(o,l,r,ques)--l,cmp.eb(l),cmp.eb(r);

	cmp=mkuni(cmp);
	ll N=len(cmp)-1;
	LazySegmentTree<AM> seg(Iota(0,N)|Transform([&](auto i){
		T ans{};
		ans[0]=cmp[i+1]-cmp[i];
		return ans;
	})|rtov);

	FOR_E(op,l,r,ques){
		l=lb(cmp,l);
		r=lb(cmp,r);
		if(op==1){
			seg.apply(l,r,1);
		}
		else{
			OUT(seg(l,r)[1]);
		}
	}
}
