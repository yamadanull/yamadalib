#include "../../template/template.hpp"
#include "../../misc/all.hpp"

void yamada::solve()
{
	ll T=2;
	out(T);
	rep(T){
		ll N=randint(1,6);
		vl A(N); each(a,A)a=randint(1,10);
		out(N);
		out(A);
	}
}
