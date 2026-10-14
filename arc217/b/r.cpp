#include "../../template/template.hpp"
#include "../../misc/all.hpp"

void yamada::solve()
{
	out(1);
	ll N=randint(1,7);
	ll K=randint(1,N+1);
	vl A(N);
	rep(i,N)A[i]=i;
	randshf(A);
	rep(N-K)A.pop_back();

	out(N,K);
	each(a,A)a++;
	out(A);
}
