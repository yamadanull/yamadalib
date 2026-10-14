#include "../../template/template.hpp"
#include "../../modint/montgomery-modint.hpp"
#include "../../segment-tree/segment-tree.hpp"
#include "../../monoid/generate-monoid.hpp"
using namespace yamada;
using mint = LazyMontgomeryModInt<998244353>;

const int K=3;
using T=array<array<mint,K>,K+1>;
const string U="RGB";
T F(T X,T Y){
	T ans;
	FOR(i,K)FOR(j,i+1,K+1){
		ans[i][j]+=X[i][j]+Y[i][j];
		FOR(m,i+1,j){
			ans[i][j]+=X[i][m]*Y[m][j];
		}
	}
	return ans;
}
T ti(){
	return T();
}
T genT(char c,ll a){
	auto ans=ti();
	FOR(i,K)if(U[i]==c){
		ans[i][i+1]+=a;
	}
	return ans;
}
using Mono=MyMonoid<T,F,ti>;

void yamada::solve()
{
	LL(N,Q);
	vl A(N); IN(A);
	STR(S);
	SegmentTree<Mono> seg(Zip(A,S)|Transform([](auto ac)->T{
		auto[a,c]=ac;
		return genT(c,a);
	})|rtov);
	FOR(Q){
		LL(op);
		if(op==1){
			LL(i,x); --i;
			seg.set(i,genT(S[i],x));
		}
		else{
			LL(l,r); --l;
			OUT(seg(l,r)[0][K]);
		}
	}
}
