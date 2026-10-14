#include "../../template/template.hpp"
#include "../../misc/all.hpp"

void yamada::solve()
{
	ll N=randint(1,8);
	vl A(N);
	each(a,A)a=randint(0,N);
	sort(all(A));
	out(N);
	out(A);
}
