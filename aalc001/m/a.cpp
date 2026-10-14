#include "../../template/template.hpp"
#include "../../segment-tree/segment-tree.hpp"
#include "../../monoid/generate-monoid.hpp"
using namespace yamada;

struct T{
};
using E=ll;
T ti(){
	T ans{};
	ans.t0=true;
	return ans;
}
T F(T X,T Y){
	if(X.t0)return Y;
	if(Y.t0)return X;
	T ans;
	ans.t0=false;
	ans.ans=Y.to[X.ans];
	FOR(i,2)ans.to[i]=Y.to[X.to[i]];
	return ans;
}
T genT(bool a){
	T ans;
	ans.t0=false;
	ans.ans=a;
	ans.to[0]=1;
	ans.to[1]=!a;
	return ans;
}
using Mono=MyMonoid<T,F,ti>;

const int LG=30;
void yamada::solve()
{
	LL(N,Q);
	vl A(N); IN(A);
	vc<SegmentTree<Mono>> segs;
	FOR(t,LG){
		segs.eb(A|Transform([&](auto a)->T{
			return genT(a>>t&1);
		})|rtov);
	}
	FOR(Q){
		LL(op);
		if(op==1){
			LL(i,x); --i;
			FOR(t,LG){
				segs[t].set(i,genT(x>>t&1));
			}
		}
		else{
			LL(l,r); --l;
			ll ans=0;
			FOR(t,LG){
				if(segs[t](l,r).ans)ans|=1LL<<t;
			}
			OUT(ans);
		}
	}
}
