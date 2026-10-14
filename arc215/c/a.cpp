#include "../../template/template.hpp"
#include "../../segment-tree/lazy-segment-tree-utility.hpp"
using namespace yamada;

void tc()
{
	inl(N);
	vl A,B,C;
	{
		V<tuple<ll,ll,ll>> cba;
		rep(N){
			inl(a,b,c); --a; --b; --c;
			cba.eb(c,b,a);
		}
		sort(all(cba)); reverse(all(cba));
		each3(c,b,a,cba){
			A.eb(a);
			B.eb(b);
			C.eb(c);
		}
	}

	AddMax_LazySegmentTree<ll,-infLL> segAL(vl(N,0));
	AddMax_LazySegmentTree<ll,-infLL> segAR(vl(N,0));
	AddMax_LazySegmentTree<ll,-infLL> segBL(vl(N,0));
	AddMax_LazySegmentTree<ll,-infLL> segBR(vl(N,0));
	rep(i,N){
		segAR.apply(A[i],A[i]+1,1);
		segBR.apply(B[i],B[i]+1,1);
	}

	/* out(A); */
	/* out(B); */
	/* out(C); */
	for(ll l=0,r=0; l<N; l=r){
		while(r<N && C[l]==C[r])++r;
		if(r==N)break;
		rep(i,l,r){
			segAL.apply(A[i],A[i]+1,1);
			segAR.apply(A[i],A[i]+1,-1);
			segBL.apply(B[i],B[i]+1,1);
			segBR.apply(B[i],B[i]+1,-1);
		}

		ll LaM=segAL.max_right(0,[](ll mx){return mx<=0;});
		ll RaM=segAR.min_left(N,[](ll mx){return mx<=0;});
		ll LbM=segBL.max_right(0,[](ll mx){return mx<=0;});
		ll RbM=segBR.min_left(N,[](ll mx){return mx<=0;});
		/* out(LaM,RaM,LbM,RbM); */
		if(LaM>=RaM && LbM>=RbM){
			die(r);
		}
	}
	die(N);
}
void yamada::solve() { ini(T); while(T--)tc(); }
