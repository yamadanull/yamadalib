#include "../../template/template.hpp"
#include "../../segment-tree/lazy-segment-tree-utility.hpp"

void yamada::solve()
{
	IN(N,Q,A=LL*N);
	auto B=A;
	each(b,B)if(b<0)b=inf;
	max_segtree<ll>segmx(A);
	min_segtree<ll>segmn(B);
	while(Q--){
		IN(op);
		if(op==1){
			IN(i,x); --i;
			segmx.set(i,x);
			segmn.set(i,x<0?inf:x);
		}
		else{
			IN(l,r); --l;
			YesNo(segmn(l,r)==inf || segmx(l,r)==segmn(l,r));
		}
	}
}
