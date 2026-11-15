#include "../../template/multitest-template.hpp"
using namespace yamada;

ll naive(ll N,vc<int> P){
	auto comp=[&](vc<int> P,ll U,vvl A)->pair<vc<int>,vvl>{
		ll par=P[U];
		each(p,P)if(p==U)p=par;
		each(a,A[U])A[par].eb(a);
		P[U]=-1;
		A[U].clear();
		return{P,A};
	};

	auto check=[&](vc<int> P,vc<int> B)->bool{
		ll N=len(P);
		vvl A(N); rep(i,N)A[i]={i};
		each(u,B){
			tie(P,A)=comp(P,u,A);
		}
		rep(i,N)if(A[0][i]!=i)return 0;
		return 1;
	};

	ll ans=0;
	nxp(N-1,[&](auto B){
		each(b,B)++b;
		if(check(P,B))++ans;
	});
	return ans;
}

void yamada::solve()
{
	IN(N);
	vc<int> P(N); in(P|Drop(1)); each(p,P)--p;
	auto ans=naive(N,P);
	out(ans);
}
