#include "../../template/multitest-template.hpp"
using namespace yamada;

map<pr<vl,ll>,ll> memo;
ll naive(vl A,ll K){
	if(A.empty())return 0;
	if(memo.count(mkp(A,K)))return memo[mkp(A,K)];
	ll N=len(A);
	ll ans=infLL;
	FOR(i,N){
		auto B=A;
		if(B[i]<=K){
			B.erase(B.begin()+i);
		}
		else{
			B[i]=(B[i]+1)/2;
			B.eb(B[i]);
		}
		Sort(B);
		amin(ans,naive(B,K+1)+1);
	}
	return memo[mkp(A,K)]=ans;
}

void yamada::solve()
{
	LL(N,K);
	vl A(N); IN(A);
	Sort(A);
	FOUT(naive(A,K));
}
