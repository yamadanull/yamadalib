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
		ErasablePriorityQueue<tuple<ll,ll,ll>>q;
		UpdateMax_LazySegmentTree<ll,-infLL>segL(vl(N,0));
		UpdateMax_LazySegmentTree<ll,-infLL>segR(vl(N,0));
		UpdateMax_LazySegmentTree<ll,-infLL>segA(A);
		rep(i,N){
			q.push(mkt(A[i],i,i+1));
			segL.update_val(i,i);
			segR.update_val(i,i+1);
		}

		ll ans=0;
		rep(i,N-1){
			auto[a,l,r]=q.top(); q.pop();
			bool fn=false;
			if(l==0)fn=true;
			else if(r==N)fn=false;
			else{
				ll L=l,R=r;
				rep(i,N){
					if(L==0)break;
					if(R==N)break;
					L=segL.get_val(L-1);
					R=segR.get_val(R);
					if(segA.get_val(L)!=segA.get_val(R-1)){
						if(segA.get_val(L)<segA.get_val(R-1))fn=false;
						else fn=true;
						break;
					}
				}
			}

			if(fn){
				ll L=segL.get_val(r);
				ll R=segR.get_val(r);
				ll b=segA.get_val(r);
				segA.update(l,R,b+1);
				segL.update(l,R,l);
				segR.update(l,R,R);
				q.push(mkt(b+1,l,R));
				q.erase(mkt(b,L,R));
				ans+=b-a;
			}
			else{
				ll L=segL.get_val(l-1);
				ll R=segR.get_val(l-1);
				ll b=segA.get_val(l-1);
				segA.update(L,r,b+1);
				segL.update(L,r,L);
				segR.update(L,r,r);
				q.push(mkt(b+1,L,r));
				q.erase(mkt(b,L,R));
				ans+=b-a;
			}
		}
		out(ans);
	}
}
