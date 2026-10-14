#include "../../template/template.hpp"
#include "../../misc/random-graph.hpp"
#include "../../misc/all.hpp"

void yamada::solve()
{
	ll N=randint(1,5);
	ll K=randint(1,N+1);
	vl A(N);
	FOR_E(a,A)a=randint(1,5);

	OUT(N,K);
	OUT(A);
}
