#include "../../template/multitest-template.hpp"
using namespace yamada;

bool cal(){
	IN(N,K,P=--INT*N);
	auto check=[&](ll msk)->bool{
		vl A,B;
		rep(i,N)(msk>>i&1?A:B).eb(P[i]);
		Sort(A);
		Sort(B);
		vl C(N);
		for(ll ai=0,bi=0,i=0; i<N; i++){
			C[i]=msk>>i&1? A[ai++]:B[bi++];
		}
		each(a,b,C|Adjacent<2>)if(a>b)return 0;
		return 1;
	};
	VVV(char,memo,2,1<<N,1<<N,2);
	return [&](this auto dfs,bool alice,ll msk,ll nsk)->bool{
		assert((msk&nsk)==0);
		auto&& mm=memo[alice][msk][nsk];
		if(mm<2)return mm;
		if((msk|nsk)==MSK(N))return mm=!(check(msk)^alice);

		rep(p,2)rep(ksk,1,1<<N)if((msk&ksk)==0 && (nsk&ksk)==0 && popcnt(ksk)<=K){
			if(!dfs(!alice,p?msk:msk|ksk,!p?nsk:nsk|ksk))return mm=1;
		}
		return mm=0;
	}(1,0,0);
}

void yamada::solve()
{
	out(cal()?"Alice":"Bob");
}
