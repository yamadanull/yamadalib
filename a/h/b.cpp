#include "../../template/template.hpp"
#include "../../segment-tree/lazy-segment-tree-utility.hpp"

void yamada::solve()
{
	const int LG=30;
	inl(N,M);
	using SEG=UpdateSum_LazySegmentTree<int,-1>;
	vc<SEG> seg;
	vl A(N); in(A);

	auto seginit=[&](){
		seg.clear();
		vv(ll,init,LG,N);
		rep(t,LG){
			rep(i,N){
				init[t][i]=A[i]>>t&1;
			}
			seg.eb(init[t]);
		}
	};

	vc<array<int,5>> lrxLR(M);
	for(auto&&[l,r,x,L,R]:lrxLR)in(l);
	for(auto&&[l,r,x,L,R]:lrxLR)in(r);
	for(auto&&[l,r,x,L,R]:lrxLR)in(x);
	for(auto&&[l,r,x,L,R]:lrxLR)in(L);
	for(auto&&[l,r,x,L,R]:lrxLR)in(R);

	inl(Q);
	rep(i,1,Q+1){
		seginit();
		ll y=i;
		inl(s,q);
		rep(j,1,q+1){
			ll z=(s+j)%M+1;
			auto[l,r,x,L,R]=lrxLR[z-1];
			ll u=min(N,max(1LL,l^y));
			ll v=min(N,max(1LL,r^y));
			ll U=min(N,max(1LL,L^y));
			ll V=min(N,max(1LL,R^y));

			ll l_=min(u,v);
			ll r_=max(u,v);
			ll L_=min(U,V);
			ll R_=max(U,V);

			--l_; --L_;
			if(z%2==0){
				rep(t,LG)if((x^y)>>t&1)seg[t].apply(l_,r_,1);
			}
			else{
				rep(t,LG)if(!((x^y)>>t&1))seg[t].apply(l_,r_,0);
			}

			ll ny=0;
			rep(t,LG){
				ny+=(1LL<<t)*seg[t](L_,R_).a.se;
			}
			y=ny%(1LL<<30);
		}
		out(y);
	}
}
