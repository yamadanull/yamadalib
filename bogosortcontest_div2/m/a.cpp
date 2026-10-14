#include "../../template/template.hpp"

void yamada::solve()
{
	LL(N);
	vl R(N-1),W(N-1); IN(R,W);
	vc<multiset<ll>> sts(N);
	FOR(i,N-1){
		ll l=i+1;
		ll r=i+1+R[i];
		FOR(j,l,r)sts[j].insert(W[i]);
	}

	ll ans=0;
	FOR(i,1,N){
		assert(!sts[i].empty());
		ans+=*sts[i].begin();
	}
	ERR(ans);

	for(int _=rdi(); _--;){
		LL(i,r,w); --i;
		FOR(j,i+1,i+1+max(r,R[i])){
			assert(!sts[j].empty());
			ans-=*sts[j].begin();
		}
		FOR(j,i+1,i+1+R[i]){
			assert(sts[j].lower_bound(W[i])!=sts[j].end());
			sts[j].erase(sts[j].lower_bound(W[i]));
		}
		FOR(j,i+1,i+1+r)sts[j].insert(w);
		FOR(j,i+1,i+1+max(r,R[i])){
			assert(!sts[j].empty());
			ans+=*sts[j].begin();
		}
		W[i]=w;
		R[i]=r;
		OUT(ans);
	}
}
