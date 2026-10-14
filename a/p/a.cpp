#include "../../template/multitest-template.hpp"
#include "../../segment-tree/dynamic-segment-tree.hpp"
#include "../../monoid/update-max.hpp"

using AM=ACTED_MONOID::Update_Max<int>;
using SEG=DynamicLazySegmentTree<AM,true>;
void yamada::solve()
{
	inl(N);
	vl A(N); in(A);
	CumulativeSum cum(A);
	vl B(N);
	rep(i,N)B[i]=A[i]+cum(0,i+1);

	auto cmp=mkuni(B);

	SEG seg(0,cmp.size());
	vc<SEG::Ptr> ps(N);
	ps[0]=seg.set_val(lb(cmp,B[0]),1);

	ll ans=1;
	if(A[0]<cum(1,N))ans=2;
	rep(i,1,N){
		ll l=bisect<ll>(-1,i,[&](ll l){return cum(l+1,i)>A[i];})-1;
		if(l<0){ps[i]=seg.cur_root;continue;}
		ll L=lb(cmp,cum(0,i));
		ll bns=seg(ps[l],0,L)+2;
		if(bns<0){ps[i]=seg.cur_root;continue;}
		ps[i]=seg.set_val(lb(cmp,B[i]),bns);

		/* err(l,i,bns); */
		if(A[i]<cum(i+1,N))amax(ans,bns+1);
		else amax(ans,bns);
	}

	out(N-ans);
}
