#include "../../template/template.hpp"
#include "../../segment-tree/lazy-segment-tree-utility.hpp"
#include "../../data-structure/erasable-priority-queue.hpp"

void yamada::solve()
{
	inl(TC);
	while(TC--)
	{
		inl(N);
		vl A(N); in(A);
		ErasablePriorityQueue<tuple<ll,ll,ll,ll>>q;
		UpdateMax_LazySegmentTree<ll,-infLL>segL(vl(N,0));
		UpdateMax_LazySegmentTree<ll,-infLL>segR(vl(N,0));
		UpdateMax_LazySegmentTree<ll,-infLL>segA(A);
		rep(i,N){
			segL.update_val(i,i);
			segR.update_val(i,i+1);
		}
		rep(i,N-1){
			q.push(mkt(abs(A[i+1]-A[i]),min(A[i],A[i+1]),i,i+1));
		}

		ll ans=0;
		rep(i,N-1){
			auto[a,b,l,m]=q.top(); q.pop();

			ans+=abs(b-a);
			ll r=segR.get_val(m);
			ll X=max(a,b)+1;
			segA.update(l,r,X);
			segL.update(l,r,l);
			segR.update(l,r,r);

			if(l>0){
				ll c=segA.get_val(l-1);
				ll l2=segL.get_val(l-1);
				q.erase(mkt(abs(c-a),min(c,a),l2,l));
				q.push(mkt(abs(c-X),min(c,X),l2,l));
			}
			if(r<N){
				ll c=segA.get_val(r);
				ll r2=segR.get_val(r);
				q.erase(mkt(abs(c-b),min(c,b),m,r));
				q.push(mkt(abs(c-X),min(c,X),r,r2));
			}
		}
		out(ans);
	}
}
