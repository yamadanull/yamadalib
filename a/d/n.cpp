#include "../../template/template.hpp"
#include "../../segment-tree/lazy-segment-tree-utility.hpp"

void yamada::solve()
{
	LL(N,B,C);
	vl A(N); IN(A);
	ll ans=-infLL;
	FOR(msk,1<<N){
		auto G=tog(msk,N);
		if(![&](){
			for(ll l=0,r=0; l<N; l=r){
				while(r<N && G[l]==G[r])++r;
				if(msk>>l&1){
					if(r-l>=C)return 0;
				}
				else{
					if(r-l>=B)return 0;
				}
			}
			return 1;
		}())continue;

		ll bns=0;
		FOR(i,N)if(msk>>i&1)bns+=A[i];
		amax(ans,bns);
	}
	OUT(ans);
}
