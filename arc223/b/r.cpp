#include "../../template/template.hpp"
#include "../../misc/all.hpp"

void yamada::solve()
{
	out(1);
	ll N=randint(2,9);
	ll K=randint(1,9);
	vl A(N);
	each(a,A)a=randint(1,10);

	out(N,K);
	out(A);
}
