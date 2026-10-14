#include "../../template/template.hpp"
#include "../../segment-tree/lazy-segment-tree-utility.hpp"
using namespace yamada;

void tc()
{
	inl(N);
	vl A(N); in(A);
	UpdateMax_LazySegmentTree<ll,-infLL> seg(A);
	minpq<tuple<ll,ll,ll,ll>> aclr;
	for(ll l=0,r=0; l<N; l=r){
		while(r<N && A[l]==A[r])++r;
		aclr.push(mkt(A[l],r-l,l,r));
	}

	ll ans=0;
	UpdateSum_LazySegmentTree<ll,-infLL> is_valid(vl(N,1));
	while(1){
		auto[a,cnt,l,r]=aclr.top(); aclr.pop();
		if(l>0 && a>=seg.get_val(l-1))continue;
		if(r<N-1 && a>=seg.get_val(r))continue;
		if(a!=seg.get_val(l))continue;
		if(cnt!=is_valid.query(l,r))continue;

		if(l==0 && r==N){
			while(cnt>1){
				if(cnt%2)++ans;
				cnt=(cnt+1)/2;
			}
			break;
		}

		ll na=infLL;
		if(l>0)amin(na,seg.get_val(l-1));
		if(r<N)amin(na,seg.get_val(r));
		while(cnt>1 && a<na){
			++a;
			if(cnt%2)++ans;
			cnt=(cnt+1)/2;
		}
		if(a<na)ans+=na-a;
		seg.update(l,r,na);
		is_valid.update(l,r,0);
		is_valid.update(l,l+cnt,1);

		ll L=seg.min_left(l,[&](ll mx){return mx<=na;});
		ll R=seg.max_right(r,[&](ll mx){return mx<=na;});
		ll ncnt=is_valid.query(L,R);
		aclr.push(mkt(na,ncnt,L,R));
	}
	out(ans);
}
void yamada::solve() { inl(T); while(T--)tc(); }
