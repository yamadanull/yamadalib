#include "../../template/template.hpp"
#include "../../segment-tree/lazy-segment-tree-utility.hpp"

void yamada::solve()
{
	IN(N,Q,S=STR);
	vl A(N+1);
	rep(i,N)A[i+1]=A[i]+(S[i]=='('?1:-1);
	min_segtree<ll> segmn(A);
	max_segtree<ll> segmx(A);
	err(A);

	auto to=mkiota(N);
	vl ans(N+1);
	rep(T,1,N+1){
		ll L=0;
		while(L<N){
			ll R=min(L+T,N);
			if(segmn(L,R)>=A[L]){
				++ans[T];
				L=R;
				continue;
			}
		}
	}
	vl ans(N+1);
	ans[1]=N;
	while(Q--)out(ans[INT()]);
}
