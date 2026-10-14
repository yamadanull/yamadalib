#include "../../template/template.hpp"
#include "../../segment-tree/lazy-segment-tree-utility.hpp"
using namespace yamada;

void tc()
{
	inl(N,K);
	vl A(N); in(A);

	set<ll> I;
	rep(K){
		inl(i); --i;
		I.insert(i);
	}

	AddMin_LazySegmentTree<ll,infLL> segmn(A);
	AddMax_LazySegmentTree<ll,-infLL> segmx(A);
	ll ans=0;
	while(1){
		vl vI;
		each(i,I)vI.eb(i);
		bool end=1;
		/* out(vI); cout.flush(); */
		rep(Ii,vI.size()){
			ll i=vI[Ii];
			if(segmn[i].a==0){
				ll l=segmx.min_left(i,[](ll mx){return mx<=0;});
				ll r=segmx.max_right(i,[](ll mx){return mx<=0;});
				if(l==0 || r==N){
					I.erase(i);
					continue;
				}
				if(Ii>0){
					ll j=vI[Ii-1];
					ll L=segmx.min_left(j,[](ll mx){return mx<=0;});
					ll R=segmx.max_right(j,[](ll mx){return mx<=0;});
					if(L==l && R==r){
						I.erase(i);
						continue;
					}
				}
				segmx.apply(l,r,1);
				segmn.apply(l,r,1);
				end=0;
				++ans;
			}
			else{
				ll l=segmn.min_left(i,[](ll mn){return mn>=1;});
				ll r=segmn.max_right(i,[](ll mn){return mn>=1;});
				if(l==0 || r==N){
					I.erase(i);
					continue;
				}
				if(Ii>0){
					ll j=vI[Ii-1];
					ll L=segmn.min_left(j,[](ll mn){return mn>=1;});
					ll R=segmn.max_right(j,[](ll mn){return mn>=1;});
					if(L==l && R==r){
						I.erase(i);
						continue;
					}
				}
				segmx.apply(l,r,-1);
				segmn.apply(l,r,-1);
				end=0;
				++ans;
			}
		}
		if(end)break;
	}

	rep(i,N)A[i]=segmx[i];

	for(ll l=0,r=0; l<N; l=r){
		while(r<N && A[l]==A[r])++r;
		++ans;
	}
	--ans;
	out(ans);
}
void yamada::solve() { ini(T); while(T--)tc(); }
