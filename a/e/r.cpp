#include "../../template/template.hpp"
#include "../../misc/all.hpp"

void yamada::solve()
{
	ll TC=1000;
	OUT(TC);
	FOR(TC){
		ll N=randint(1,9);
		ll K=randint(0,N+1);
		vl A(N);
		FOR_E(a,A)a=randint(1,N+1);

		OUT(N,K);
		OUT(A);
	}
}
