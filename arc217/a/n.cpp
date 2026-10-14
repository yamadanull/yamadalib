#include "../../template/template.hpp"
using namespace yamada;

void tc()
{
	inl(N);
	vl memo(1<<N);
	rep(msk,1<<N){
		rep(i,N)if(msk>>i&1){
			memo[msk]^=i+1;
		}
	}

	vl dp(1<<N,infLL);
	dp[0]=0;
	rep(msk,1<<N){
		rep(i,N)if(!(msk>>i&1)){
			ll nsk=msk|(1<<i);
			amin(dp[nsk],dp[msk]+memo[nsk]);
		}
	}

	out(dp.back());
}
void yamada::solve() { ini(T); while(T--)tc(); }
