#include "../../template/multitest-template.hpp"
#include "../../segment-tree/lazy-segment-tree-utility.hpp"

void yamada::solve()
{
	LL(N);
	vl A(N); IN(A);
	min_segtree<ll> seg(A);
	if(A.front()>A.back())DIE(-1);
	ll ans=0;
	FOR(i,1,N-1){
		if(A.front()>A[i])DIE(-1);
		ll to=seg(i,N);
		ans+=A[i]-to;
	}
	OUT(ans);
}
