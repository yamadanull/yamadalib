#include "../../template/template.hpp"
#include "../../misc/all.hpp"

void yamada::solve()
{
	ll N=450;
	ll W=randint(1,N);
	ll D=randint(2,N*N-N+1);
	vl A(N-1);
	each(a,A)a=randint(1,1e6);
	out(N,W,D);
	out(A);
}
