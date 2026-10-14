#include "../../template/template.hpp"
#include "../../modint/montgomery-modint.hpp"
#include "../../monoid/add-minmincnt.hpp"
#include "../../segment-tree/lazy-segment-tree.hpp"

using mint = LazyMontgomeryModInt<998244353>;
void yamada::solve()
{
	LL(N,Q);
	LazySegmentTree<ACTED_MONOID::Add_MinMincnt<ll>> seg(Iota(0,N)|Transform([](auto i){return pl{0,i+1};}));

	vvc<tuple<ll,ll,ll>> ques(N);
	FOR(Q){
		LL(a,b,c,d); --a; --b;
		ques[a].eb(b,d,1);
		if(c<N)ques[c].eb(b,d,-1);
	}

	mint ans=0;
	FOR(i,N){
		FOR_E(l,r,a,ques[i])seg.apply(l,r,a);
		auto[mn,cnt]=seg();
		ERR(mn,cnt);
		if(mn==0)ans+=cnt*(i+1);
	}
	OUT(ans);
}
