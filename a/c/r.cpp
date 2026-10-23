#include "../../template/template.hpp"
#include "../../misc/all.hpp"

void yamada::solve()
{
	ll T=3;
	out(T);
	while(T--){
		ll N=randint(1,20);
		vl A(N);
		each(a,A)a=randint(1,10);

		out(N);
		out(A);
	}
}
