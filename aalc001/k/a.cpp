#include "../../template/template.hpp"
#include "../../segment-tree/lazy-segment-tree-utility.hpp"
#include "../../modint/montgomery-modint.hpp"
#include "../../segment-tree/segment-tree.hpp"
#include "../../monoid/generate-monoid.hpp"
using namespace yamada;

using mint = LazyMontgomeryModInt<998244353>;
struct T{
	ll siz;
	array<mint,2> A;
};
T ti(){
	return T{};
}
T F(T X,T Y){
	if(X.siz==0)return Y;
	if(Y.siz==0)return X;
	auto ans=X;
	ans.siz+=Y.siz;
	ans.A[0]+=Y.A[0];
	ans.A[1]+=Y.A[1]+Y.A[0]*X.siz;
	return ans;
}
T genT(bool b,ll a){
	if(!b)return ti();
	T ans;
	ans.siz=1;
	ans.A={a,a};
	return ans;
}
using Mono=MyMonoid<T,F,ti>;

void yamada::solve()
{
	ERR(ti().siz);
	ERR(ti().A);
	auto[A,B,ques]=[&]()->tuple<vl,vl,vp>{
		LL(N,Q);
		vl init(N); IN(init);

		vp ques(Q);
		vl A{init};
		FOR(i,Q){
			LL(op);
			if(op<=2){
				LL(x);
				A.eb(x);
				ques[i]={op,x};
			}
			else ques[i]={op,-1};
		}
		Sort(A);
		Sort(init);

		N=len(A);
		ll M=len(init);
		vl B(N);
		for(ll l=0,r=0; l<M; l=r){
			while(r<M && init[l]==init[r])++r;
			ll L=lb(A,init[l]);
			FOR(i,L,L+r-l)B[i]=1;
		}
		return{A,B,ques};
	}();
	ERR(A);
	ERR(B);

	ll N=len(A);
	SegmentTree<Mono> seg(Iota(0,N)|Transform([&](auto i)->T{
		return genT(B[i],A[i]);
	})|rtov);
	min_segtree<ll> segB(B);
	FOR_E(op,x,ques){
		if(op==1){
			ll i=lb(A,x);
			i=segB.max_right(i,[](ll mx){return mx>=1;});
			seg.set(i,genT(B[i]=1,x));
			segB.set(i,1);
		}
		else if(op==2){
			ll i=lb(A,x);
			i=segB.max_right(i,[](ll mx){return mx>=1;})-1;
			seg.set(i,genT(B[i]=0,x));
			segB.set(i,0);
			ERR(i,B);
		}
		else{
			OUT(seg().A[1]);
		}
	}
}
