#include "../../template/template.hpp"
#include "../../segment-tree/lazy-segment-tree-utility.hpp"

void yamada::solve()
{
	inl(N);
	vl A(N),B(N); in(A,B);
	AddMax_LazySegmentTree<ll,-infLL> seg(A);
	AddMax_LazySegmentTree<ll,-infLL> teg(B);
	// yoko
	map<ll,ll>mp;
	rep(i,1,N){
		ll check=seg.max_right(1,[&](ll mx){return mx<=A[i];})-i;
		if(check<=0)continue;
		ll a=teg.max_right(1,[&](ll mx){return mx<A[i];})-1;
		ll b=seg.max_right(i+1,[&](ll mx){return mx<A[i];})-i;
		if(b>0)mp[A[i]]+=a*b;
	}
	// tate
	rep(j,1,N){
		// その数字が支配する領域はあるか
		ll check=teg.max_right(1,[&](ll mx){return mx<=B[j];})-j;
		if(check<=0)continue;
		ll a=seg.max_right(1,[&](ll mx){return mx<=B[j];})-1;
		ll b=teg.max_right(j+1,[&](ll mx){return mx<B[j];})-j;
		if(b>0)mp[B[j]]+=a*b;
	}
	rep(i,N)mp[A[i]]++;
	rep(i,1,N)mp[B[i]]++;

	pl ans=mkp(-infLL,-infLL);
	each2(a,c,mp){
		amax(ans,mkp(c,a));
	}
	out(ans.se,ans.fi);
}
