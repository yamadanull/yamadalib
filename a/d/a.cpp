#include "../../template/multitest-template.hpp"
#include "../../segment-tree/lazy-segment-tree-utility.hpp"

void yamada::solve()
{
	IN(N,A=LL*N);
	auto B=mkrui(A);
	if(Min(B)<0)DIE(-1);
	auto cmp=mkuni(B);
	ll M=len(cmp);
	sum_segtree<ll> seg(vl(M,0));
	ll ans=0;
	rep(r,N+1){
		ll ci=lb(cmp,B[r]);
		ans+=seg(ci+1,M);
		seg.set(ci,seg[ci]+1);
	}
	out(ans);
}
