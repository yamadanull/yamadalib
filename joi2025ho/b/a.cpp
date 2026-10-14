#include "../../template/template.hpp"
#include "../../segment-tree/lazy-segment-tree-utility.hpp"

void yamada::solve()
{
	inl(N);
	vl A(N),B(N); in(A,B);
	rep(i,N)B.eb(B[i]),A.eb(A[i]);
	auto Brui=mkrui(B);
	vl A_Brui(N*2);
	rep(i,N*2)A_Brui[i]=A[i]-Brui[i];
	AddMax_LazySegmentTree<ll,-infLL> seg(A_Brui);
	/* out(Brui); */
	/* out(A_Brui); */

	ll ans=infLL;
	rep(st,N){
		ll bns=seg.query(st,st+N);
		bns+=Brui[st];
		amin(ans,bns);
	}
	out(max(0LL,ans));
}
