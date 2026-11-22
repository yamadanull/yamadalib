#include "../../template/multitest-template.hpp"
using namespace yamada;

ll naive(vl A){
	ll N=len(A);
	queue<vl> q;
	q.emplace(A);
	map<vl,ll>memo;
	memo[A]=0;
	while(!q.empty()){
		auto B=q.front(); q.pop();
		if(All(B,[&](auto b){return b>=0;}))return memo[B];
		rep(i,1,N){
			auto C=B;
			C[i-1]+=C[i];
			if(i<N-1)C[i+1]+=C[i];
			C[i]*=-1;
			if(!memo.count(C)){
				memo[C]=memo[B]+1;
				q.emplace(C);
			}
		}
	}
	return -1;
}

void yamada::solve()
{
	/* IN(N,M); */
	/* vl cur; */
	/* [&](this auto dfs)->void{ */
	/* 	if(len(cur)==N){ */
	/* 		ll niv=naive(cur); */
	/* 		err(cur,naive(cur)); */
	/* 		if(niv>=0){ */
	/* 			ll ans=0; */
	/* 			CumulativeSum cum(cur); */
	/* 			rep(i,N)rep(j,i+1,N+1){ */
	/* 				if(cum(i,j)<0)++ans; */
	/* 			} */
	/* 			assert(ans==niv); */
	/* 		} */
	/* 		assert(niv<0 xor Min(mkrui(cur))>=0); */
	/* 		return; */
	/* 	} */
	/* 	rep(i,-M,M+1){ */
	/* 		cur.eb(i); */
	/* 		dfs(); */
	/* 		cur.pop_back(); */
	/* 	} */
	/* }(); */
	IN(N,A=LL*N);
	out(naive(A));
}
