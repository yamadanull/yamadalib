#include "../../template/multitest-template.hpp"
using namespace yamada;

bool check(ll N,vint A){
	N=N*2-1;
	vl fn(N,1);
	ll M=len(A);
	FOR(i,N)FOR(j,N){
		if(!dfs(i,j,0))return 0;
	}
	return 1;
}

vint naive(ll N){
	FOR(x,1,N*3+1){
		ERR(x);
		vint ans;
		auto F=[&](vint bns){
			/* if(!ans.empty())return; */
			if(check(N,bns)){
				ERR(bns);
				ans=bns;
			}
		};
		Product(x,N*2-1,F);
		if(!ans.empty())return ans;
	}
	return{};
}

void yamada::solve()
{
	LL(N);
	naive(N);
}
