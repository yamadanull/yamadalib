#include "../../template/template.hpp"
#include "../../segment-tree/lazy-segment-tree.hpp"
#include "../../modint/montgomery-modint.hpp"

void yamada::solve()
{
	using mint = LazyMontgomeryModInt<998244353>;
	auto F=[](mint a,mint b)->mint{return a+b;};
	auto G=[](mint a,mint b)->mint{return a*b;};

	inl(N);
	auto rot=[&](vl& P){ vl pos(N); rep(i,N)pos[P[i]]=i; reverse(all(pos)); P=pos; };
	
	auto lemma1=[&](vl& P)->mint{
		mint ans=0;
		rep(i,1,N)ans+=((mint)2).pow(i)-1;
		return ans*(N-1);
	};
	auto lemma2=[&](vl& P)->mint{
		LazySegmentTree<mint,mint,decltype(F),decltype(G),decltype(G)>seg(V<mint>(N-1,1),F,G,G,0,1);
		mint ans=0;
		rep(i,N-1){
			seg.update(P[i],N-1,2);
			ans+=seg.query(0,N-1)-(N-1);
		}
		return ans;
	};

	vl P(N); in(P); each(p,P)--p;
	mint ans=(((mint)2).pow(N)-1)*(N-1)*(N-1);
	mint bns,cns;
	rep(x,4){
		bns+=lemma1(P);
		cns+=lemma2(P);
		rot(P);
	}
	out(ans-bns+cns);
}
