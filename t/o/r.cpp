#include "../../template/template.hpp"
#include "../../misc/all.hpp"

void yamada::solve()
{
	ll N=3;
	ll M=randint(1,1<<N);
	vl P(1<<N); rep(i,1<<N)P[i]=i+1;
	randshf(P);

	vl W,L;
	rep(i,M){
		vl p=randset(1,1<<N,2);
		W.eb(p[0]);
		L.eb(p[1]);
	}

	out(N,M);
	out(P);
	rep(i,M)out(W[i],L[i]);
}
