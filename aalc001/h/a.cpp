#include "../../template/template.hpp"
#include "../../modint/montgomery-modint.hpp"
#include "../../segment-tree/segment-tree.hpp"
#include "../../monoid/generate-monoid.hpp"
using namespace yamada;

struct T{
	bool usemod;
	ll a,b; // !usemod -> b=0
};
T ti(){
	return{0,0,0};
}
T F(T X,T Y){
	if(Y.usemod){
		return{true,X.a+X.b+Y.a,Y.b};
	}
	if(X.usemod){
		return{true,X.a,X.b+Y.a+Y.b};
	}
	return{false,X.a+Y.a};
}
T genT(ll a){
	if(a==0)return{true,0,0};
	return{false,a,0};
}
using Mono=MyMonoid<T,F,ti>;

using mint = LazyMontgomeryModInt<998244353>;
void yamada::solve()
{
	LL(N,Q);
	vl A(N); IN(A);
	SegmentTree<Mono> seg(A|Transform([](auto a)->T{
		return genT(a);
	})|rtov);
	FOR(Q){
		LL(op);
		if(op==1){
			LL(i,x); --i;
			seg.set(i,genT(x));
		}
		else{
			LL(l,r,x); --l;
			auto t=seg(l,r);
			if(t.usemod){
				x+=t.a;
				x%=mint::get_mod();
				x+=t.b;
			}
			else{
				x+=t.a;
			}
			OUT(x);
		}
	}
}
