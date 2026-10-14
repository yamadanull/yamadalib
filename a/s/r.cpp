#include "../../template/template.hpp"
#include "../../misc/all.hpp"

void yamada::solve()
{
	ll T=30;
	out(T);
	rep(T){
		ll N=randint(2,9);
		ll K=randint(1,N/2+1);
		vl A(N);
		each(a,A)a=randint(1,N+1);

		out(N,K);
		out(A);
	}
}
