#include "../../template/template.hpp"
#include "../../segment-tree/lazy-segment-tree-utility.hpp"

void yamada::solve()
{
	IN(N,L,R,A=LL*N); ++R;
	auto B=mkrui(A);
	auto cmp=mkuni(B);
	ll M=len(cmp);
	sum_segtree<ll> seg(vl(M,0));
	ll ans=0;
	each(b,B|Rev){
		ll ci=lb(cmp,b);
		ll cL=lb(cmp,b+L);
		ll cR=lb(cmp,b+R);
		ans+=seg(cL,cR);
		seg.set(ci,seg[ci]+1);
	}
	out(ans);
}
