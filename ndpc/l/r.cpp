#include "../../template/template.hpp"
#include "../../misc/all.hpp"

void yamada::solve()
{
	ll N=randint(3,15);
	vl A(N);
	rep(i,N)A[i]=i+1;
	randshf(A);

	out(N);
	out(A);
}
