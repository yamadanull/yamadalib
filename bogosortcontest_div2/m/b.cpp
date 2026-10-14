#include "../../template/template.hpp"
#include "../../segment-tree/segment-tree.hpp"
#include "../../monoid/generate-monoid.hpp"
using namespace yamada;

const ll K=6;
using T0=array<array<ll,K>,K>;
using T=pr<T0,ll>;
T ti(){
	T0 ans;
	Fill(ans|Join,infLL);
	return {ans,0};
}
T F(T X,T Y){
	if(X==ti())return Y;
	if(Y==ti())return X;
	auto ans=ti().fi;
	auto[x,lsiz]=X;
	auto[y,rsiz]=Y;
	FOR(i,K)FOR(j,K)FOR(k,K)FOR(l,K){ // TO OPT!!!!!!!!!!!!
		if(j>k || lsiz+k<K){
			ll I=(k? k+lsiz: i);
			ll J=max(j-rsiz,l);
			amin(ans[I][J],x[i][j]+y[k][l]);
		}
	}
	return{ans,lsiz+rsiz};
}
T genT(ll r,ll w){
	auto ans=ti().fi;
	FOR(msk,1<<r){
		ll I=0;
		FOR(i,r)if(!(msk>>i&1))I=i+1;
	}
	ans[1][0]=0;
	return{ans,1};
}
using Mono=MyMonoid<T,F,ti>;

void yamada::solve()
{
	LL(N);
	vl R(N-1),W(N-1); IN(R,W);
	SegmentTree<Mono> seg(Zip(R,W)|Transform([&](auto rw){
		auto[r,w]=rw;
		return genT(r,w);
	})|rtov);
	FOR(i,N-1)ERR(i,seg[i].fi);

	for(int _=rdi(); _--;){
		LL(i,r,w); --i;
		seg.set(i,genT(r,w));
		auto A=seg().fi;
		ERR(A);
		OUT(A[0][1]);
	}
}
