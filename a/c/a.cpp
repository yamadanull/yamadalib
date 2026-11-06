#include "../../template/multitest-template.hpp"

void yamada::solve()
{
	IN(N);
	ll T=msb(N)+1;
	ll K=MSK(T);
	ll M=0;
	rep(i,1,N+1)M^=i;
	/* err(K,M); */
	rep(t,2){
		vl pos;
		ll m=M;
		if(t){m^=3;pos.eb(1);}
		rep(t2,1,T)if(!(m>>t2&1)){
			m^=1LL<<t2;
			m^=1LL<<t2+1;
			pos.eb(1LL<<t2);
		}
		err(m,K);

		if(m>=K*2){
			vl ans(N,0);
			each(t,pos)ans[t-1]=1;
			DIE(ans);
		}
	}
	assert(0);
}
