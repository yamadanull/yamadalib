#include "../../template/multitest-template.hpp"

void yamada::solve()
{
	LL(N);
	auto A=rds()|Transform([&](auto c)->ll{
		if(c=='(')return 0;
		if(c==':')return 1;
		return 2;
	})|rtov;

	vv(ll,dp,N+1,3,infLL); // iまで、最後がj
	dp[0][0]=0;
	FOR(i,N)FOR(j,3)if(dp[i][j]<infLL){
		ll J=A[i];
		if(j+1==J){
		}
	}

	OUT(N-Min(dp.back())*2);
}
