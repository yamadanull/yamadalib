#include "../../template/template.hpp"
#include "../../misc/all.hpp"

void yamada::solve()
{
	ll N=randint(2,1000);
	ll K=randint(0,1000);
	vl A(N);
	each(a,A)a=randint(0,100);

	out(N,K);
	out(A);
}
