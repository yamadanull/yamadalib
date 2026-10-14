#include "../../template/template.hpp"
#include "../../segment-tree/lazy-segment-tree.hpp"
#include "../../monoid/generate-monoid.hpp"
using namespace yamada;

const int K=3;
using T=array<ll,K>;
struct E{
	array<ll,K> to;
	array<ll,K> ad; // swapあとに加算
};
T ti(){
	T ans;
	Fill(ans,-infLL);
	return ans;
}
E ei(){
	E ans;
	Fill(ans.ad,0);
	FOR(i,K)ans.to[i]=i;
	return ans;
}
T F(T X,T Y){
	FOR(i,K)amax(X[i],Y[i]);
	return X;
}
T G(T X,E A,ll){
	auto ans=X;
	FOR(i,K)ans[A.to[i]]=X[i];
	FOR(i,K)ans[i]+=A.ad[i];
	return ans;
}
E H(E A,E B){
	auto ans=B;
	FOR(i,K)ans.to[i]=B.to[A.to[i]];
	FOR(i,K)ans.ad[B.to[i]]+=A.ad[i];
	/* FOR(i,K)ans.ad[i]+=A.ad[B.to[i]]; */
	return ans;
}
using AM=MyActedMonoid<T,E,F,G,H,ti,ei>;

void yamada::solve()
{
	LL(N,Q);
	VV(ll,A,K,N); IN(A);
	FOR_E(a,A)a=mkrui(a);
	LazySegmentTree<AM> seg(Iota(0,N+1)|Transform([&](auto i)->T{
		T ans;
		FOR(I,K)ans[I]=A[I][i];
		return ans;
	})|rtov);

	auto sw=[&](ll M,ll I,ll J){
		auto A=ei();
		swap(A.to[I],A.to[J]);
		auto B=ei();
		B.ad[I]=seg[M][J]-seg[M][I];
		B.ad[J]=-B.ad[I];
		seg.apply(0,M,A);
		seg.apply(M,N+1,B);
	};
	FOR(Q){
		LL(op); --op;
		if(op<K){
			LL(l,r); --l;
			sw(l,op,(op+1)%K);
			sw(r,op,(op+1)%K);
		}
		else{
			LL(i); --i;
			auto ans=seg.max_right(i,[&](auto mx){return mx[0]<=seg[i][0];});
			OUT(ans);
		}
	}
}
