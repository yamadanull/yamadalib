#include "../../template/template.hpp"
#include "../../misc/all.hpp"

void yamada::solve()
{
	out(1);
	ll N=randint(1,7);
	vl A(N);
	each(a,A)a=randint(-10,7);
	out(N);
	out(A);
}
