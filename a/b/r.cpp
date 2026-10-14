#include "../../template/template.hpp"
#include "../../misc/all.hpp"

void yamada::solve()
{
	ll TC=1;
	out(TC);
	while(TC--){
		ll N=randint(1,10);
		vl A(N);
		each(a,A)a=randint(1,10);
		auto B=mkiota(N);
		each(b,B)++b;

		out(N);
		out(A);
		out(B);
	}
}
