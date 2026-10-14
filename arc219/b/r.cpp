#include "../../template/template.hpp"
#include "../../misc/all.hpp"

void yamada::solve()
{
	out(1);
	ll N=randint(1,9);
	vl A(N); rep(i,N)A[i]=i+1;
	randshf(A);

	out(N);
	out(A);
}
