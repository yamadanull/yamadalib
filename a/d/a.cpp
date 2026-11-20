#include "../../template/template.hpp"
#include "../../monoid/generate-monoid.hpp"
#include "../../segment-tree/lazy-segment-tree-utility.hpp"
#include "../../modint/montgomery-modint.hpp"
using namespace yamada;

using mint = LazyMontgomeryModInt<998244353>;
using T=pair<mint,mint>;
using E=mint;
T F(T a,T b){return{a.fi+b.fi,a.se+b.se};}
T G(T a,E f,ll siz){
	a.se+=f*f*siz;
	a.se+=a.fi*f*2;
	a.fi+=f*siz;
	return a;
}
E H(E f,E g){return f+g;}
T ti(){return{0,0};}
E ei(){return 0;}
using AM=MyActedMonoid<T,E,F,G,H,ti,ei>;

void yamada::solve()
{
	IN(N,A=LL*N);
	vl stkmn{-1},stkmx{-1};
	LazySegmentTree<AM>seg(vc<T>(N,ti()));
	mint ans=0;
	rep(i,N){
		while(len(stkmn)>=2 && A[stkmn.back()]>=A[i]){
			ll k=stkmn.back(); stkmn.pop_back();
			ll j=stkmn.back();
			seg.apply(j+1,k+1,A[k]-A[i]);
		}
		while(len(stkmx)>=2 && A[stkmx.back()]<=A[i]){
			ll k=stkmx.back(); stkmx.pop_back();
			ll j=stkmx.back();
			seg.apply(j+1,k+1,A[i]-A[k]);
		}
		stkmx.eb(i);
		stkmn.eb(i);
		err(seg.get());
		err(stkmn);
		err(stkmx);
		ans+=seg().se;
	}
	out(ans);
}
