#include "../../template/template.hpp"
#include "../../segment-tree/segment-tree.hpp"
#include "../../monoid/generate-monoid.hpp"
using namespace yamada;

const int K=3;
using T=array<array<array<ll,2>,2>,K>;
T ti(){
	T ans{};
	Fill(ans|Join|Join,-infLL);
	return ans;
}
T F(T X,T Y){
	if(X==ti())return Y;
	if(Y==ti())return X;
	auto ans=ti();
	FOR(i,K)FOR(j,2)FOR(k,2)if(X[i][j][k]>-infLL){
		FOR(a,K)FOR(b,2)FOR(c,2)if(Y[a][b][c]>-infLL){
			ll p=i+a-(k&b);
			if(p>=K)continue;
			ll q=j;
			ll r=c;
			/* ERR(i,j,k,a,b,c,p,q,r); */
			amax(ans[p][q][r],X[i][j][k]+Y[a][b][c]);
		}
	}
	return ans;
}
T genT(ll a){
	auto ans=ti();
	ans[0][0][0]=0;
	ans[1][1][1]=a;
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
	FOR(i,N)ERR(seg[i]);
	FOR(Q){
		LL(op);
		if(op==1){
			LL(i,x); --i;
			seg.set(i,genT(x));
		}
		else{
			LL(l,r); --l;
			ERR(seg(l,r));
			OUT(Max(seg(l,r)|Join|Join));
		}
	}
}
