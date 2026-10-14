#include "../../template/template.hpp"
#include "../../misc/all.hpp"
using namespace yamada;

void yamada::solve()
{
	ll TC=1;
	out(TC);
	while(TC--){
		ll N=randint(1,10);
		vl A(N),B(N);
		each(a,A)a=randint(0,2);
		each(a,B)a=randint(0,2);

		out(N);
		out(A);
		out(B);
	}
}
