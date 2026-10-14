#include "../../template/template.hpp"
#include "../../misc/compress.hpp"
#include "../../segment-tree/lazy-segment-tree-utility.hpp"
using namespace yamada;

void tc()
{
	inl(N,L,R);
	vl A(N); in(A);
	vl xs=A;
	vp lr; // 禁止区間
	rep(i,N){
		ll l=A[i]-L+1;
		ll r=A[i]+L;
		lr.eb(l,r);
		xs.eb(l); xs.eb(r);
		xs.eb(l-1); xs.eb(r-1);

		ll l2=A[i]-R;
		ll r2=A[i]+R+1;
		xs.eb(l2); xs.eb(r2);
		xs.eb(r2-1);
	}

	xs.eb(-infLL);
	xs.eb(infLL);
	/* xs=mkuni(xs); */
	compress cmp(xs);
	/* out(xs); */
	ll M=cmp.size();

	UpdateMin_LazySegmentTree<ll,infLL> seg(vl(M,0));
	each2(l,r,lr)seg.update(cmp(l),cmp(r),1);
	/* rep(i,M)cout<<seg.get_val(i)<<(i==M-1? "\n":" "); */

	UpdateMax_LazySegmentTree<ll,-infLL> ans(vl(M,0));
	rep(i,N){
		ll l=cmp(A[i]-R);
		ll r=cmp(A[i]+R+1);
		/* if(N==3)out("l,r:",l,r); */
		{
			ll ps=ans.max_right(l,[&](ll mx){return mx<=0;});
			/* if(N==3)out("ps:",ps); */
			if(ps<r)continue;
		}
		{
			ll ps=seg.min_left(r,[&](ll mn){return mn>=1;})-1;
			/* if(N==3)out("ps:",ps); */
			if(ps<l)die(-1);
			ans.update_val(ps,1);
		}
	}

	vl bns;
	rep(i,M)if(ans.get_val(i)>=1)bns.eb(cmp[i]);
	out(bns.size());
	out(bns);
}
void yamada::solve() { inl(T); while(T--)tc(); }
