#include "../../template/template.hpp"
#include "../../segment-tree/segment-tree.hpp"
#include "../../monoid/make-monoid.hpp"
using namespace yamada;

// [左端通る、右端通る、全部通る、全部通らない、答え
using T=tuple<ll,ll,ll,ll,ll>;
T ti(){return{-infLL,-infLL,-infLL,-infLL,-infLL};};
T F(T x,T y){
	if(y==ti())return x;
	if(x==ti())return y;
	auto[lans,rans,aans,nans,ans]=x;
	auto[lbns,rbns,abns,nbns,bns]=y;

	ll lcns=lans+nbns;
	amin(lcns,aans+lbns);

	ll rcns=nans+rbns;
	amin(rcns,rans+abns);

	ll acns=aans+abns;
	ll ncns=nans+nbns;
	ll cns=infLL;
	amin(cns,ans+nbns);
	amin(cns,nans+bns);
	amin(cns,rans+lbns);
	amin(cns,lcns);
	amin(cns,rcns);
	amin(cns,acns);
	amin(cns,ncns);
	return{lcns,rcns,acns,ncns,cns};
}

T getT(ll a){
	if(a==0)return{1,1,1,0,0};
	return{0,0,0,a,0};
}

void yamada::solve()
{
	inl(N,Q);
	vl A(N); in(A);
	V<T> init;
	each(a,A)init.eb(getT(a));

	SegmentTree<MyMono<T,F,ti>> seg(init);

	while(Q--){
		inl(i,a); --i;
		seg.set(i,getT(a));
		ll ans=get<4>(seg.prod().a);
		out(ans);
	}
}
