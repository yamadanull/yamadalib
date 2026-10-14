#include "../../template/template.hpp"
#include "../../segment-tree/segment-tree.hpp"
#include "../../monoid/generate-monoid.hpp"
using namespace yamada;

struct T{
	ll lenL,lenR,valL,valR,ans;
	bool all;
};
T ti(){
	return T{-1,-1,-1,-1,-1,0};
}
T F(T X,T Y){
	if(X.valL<0)return Y;
	if(Y.valL<0)return X;
	T ans;
	ans.lenL=(X.all && X.valL==Y.valL? X.lenL+Y.lenL: X.lenL);
	ans.lenR=(Y.all && X.valR==Y.valR? X.lenR+Y.lenR: Y.lenR);
	ans.valL=X.valL;
	ans.valR=Y.valR;
	ans.ans=max({X.ans,Y.ans,ans.lenL,ans.lenR});
	if(X.valR==Y.valL)amax(ans.ans,X.lenR+Y.lenL);
	ans.all=X.all && Y.all && X.valL==Y.valL;
	return ans;
}
T genT(ll a){
	T ans;
	ans.valL=ans.valR=a;
	ans.lenL=ans.lenR=1;
	ans.ans=1;
	ans.all=1;
	return ans;
}
using Mono=MyMonoid<T,F,ti>;

void yamada::solve()
{
	LL(N,Q);
	vl A(N); IN(A);
	SegmentTree<Mono> seg(A|Transform([](auto a)->T{
		return genT(a);
	})|rtov);
	FOR(Q){
		LL(op);
		if(op==1){
			LL(i,x); --i;
			seg.set(i,genT(x));
		}
		else{
			LL(l,r); --l;
			OUT(seg(l,r).ans);
		}
	}
}
