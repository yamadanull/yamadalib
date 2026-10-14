#include "../../template/template.hpp"
#include "../../data-structure/union-find.hpp"
#include "../../segment-tree/lazy-segment-tree-utility.hpp"
#include "../../misc/compress.hpp"

void yamada::solve()
{
	inl(N,M,P);
	vl xs{infLL};
	V<tuple<ll,ll,ll>>abc; {
		UnionFind uf(N);
		rep(i,M){
			inl(a,b,c); --a; --b;
			xs.eb(c);
			abc.eb(a,b,c);
			uf.unite(a,b);
		}
		if(uf.size(0)<N){
			inl(Q);
			while(Q--)out("No");
			return;
		}
	}

	xs=mkuni(xs);
	compress cmp(xs);

	// idx after compress
	vvl B(cmp.size()),C(N);
	each3(a,b,c,abc)C[b].eb(cmp(c)),B[cmp(c)].eb(b);
	rep(i,1,N)B.back().eb(i),C[i].eb(B.size()-1);
	each(c,C)c=mkuni(c);

	// closed interval
	// in: idx compressed
	// out: idx not compressed
	vl R(cmp.size()); {
		AddMin_LazySegmentTree<ll,infLL> seg(vl(N,0));
		ll r=cmp.size()-1;
		rep(ci,cmp.size()){
			each(b,B[ci])seg.update_val(b,1);
			if(seg.query(1,N)>0){ r=ci; break; }
		}
		R[0]=cmp[r];
		rep(l,1,cmp.size()){
			vl upd; // unreachable B
			each(b,B[l-1]){
				seg.update_val(b,-1);
				if(seg.query(1,N)<=0)upd.eb(b);
			}

			ll nr=r;
			each(b,upd){
				ll ci=lb(C[b],l);
				assert(ci<C[b].size());
				amax(nr,C[b][ci]);
			}
			rep(ci,r+1,nr+1)each(b,B[ci])seg.update_val(b,1);
			assert(seg.query(1,N)>=1);
			R[l]=cmp[nr];
			r=nr;
		}
	}

	vl RmL=R; rep(i,cmp.size())RmL[i]-=cmp[i];
	AddMin_LazySegmentTree<ll,infLL> seg(RmL);
	inl(Q);
	while(Q--){
		inl(l,r,x);
		ll ans=infLL;

		// r is fixed
		ll pos=bisect<ll>(0,cmp.size(),[&](ll ci){return R[ci]<=r;})-1;
		if(pos>=0)amin(ans,l-cmp[pos]);

		// r is not fixed
		if(pos+1<=l){
			ll ci=lb(xs,l);
			ll bns=seg.query(pos+1,ci)+l;
			assert(bns>r);
			bns-=r;
			amin(ans,bns);
		}
		// l is fixed
		{
			ll ci=lb(xs,l);
			amin(ans,R[ci]-r);
		}
		YesNo(ans<=x);
	}
}
