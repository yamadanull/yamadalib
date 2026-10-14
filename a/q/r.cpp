#include "../../template/template.hpp"
#include "../../misc/all.hpp"

void yamada::solve()
{
	ll N=randint(1,10);
	ll Q=randint(1,10);
	vl A(N);
	each(a,A)a=randint(1,10);
	out(N,Q);
	out(A);
	while(Q--){
		ll k=randint(0,N)+1;
		ll x=randint(1,10);
		out(k,x);
	}
}
