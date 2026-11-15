#include "../../template/template.hpp"
#include "../../segment-tree/lazy-segment-tree-utility.hpp"

void yamada::solve()
{
	IN(N,K,A=LL*N);
	if(K>N)DIE(-1);
	Sort(A);
	min_segtree<ll> seg(vl(N+1,infLL));
	seg.set(0,-A[0]);
	rep(i,1,N+1){
		ll L=i-K;
		if(L<0)continue;
		ll d=A[i-1]+seg(0,L+1);
		err(L,i,d);
		if(i==N){
			DIE(d);
		}
		else seg.set(i,d-A[i]);
	}
}
