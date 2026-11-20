#include "../../template/template.hpp"
#include "../../segment-tree/lazy-segment-tree-utility.hpp"

void yamada::solve()
{
	IN(N,A=LL*N);
	vl cmp;
	each(a,A)cmp.eb(a),cmp.eb(a+1),cmp.eb(a-1);
	cmp=mkuni(cmp);
	ll M=len(cmp);
	min_segtree<ll>seg(vl(M,0));

	ll X=0;
	each(x,A){
		ll cx=lb(cmp,x);
		seg.set(cx,1);
		ll CX=lb(cmp,X);
		if(x==X){
			ll CL=seg.min_left(cx,[&](ll mn){return mn>=1;})-1;
			ll CR=seg.max_right(cx,[&](ll mn){return mn>=1;});
			ll XL=cmp[CL];
			ll XR=cmp[CR];
			if(X-XL<XR-X)X=XL;
			else X=XR;
		}
	}
	out(X);
}
