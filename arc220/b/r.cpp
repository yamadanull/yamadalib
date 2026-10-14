#include "../../template/template.hpp"
#include "../../misc/all.hpp"

void yamada::solve()
{
	out(1);
	ll N=randint(2,9);
	vl A(N),B(N);
	each(a,A)a=randint(0,N)+1;
	each(b,B)b=randint(0,N)+1;
	out(N);
	out(A);
	out(B);
}
