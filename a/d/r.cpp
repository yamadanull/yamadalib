#include "../../template/template.hpp"
#include "../../misc/random-graph.hpp"
#include "../../misc/all.hpp"

void yamada::solve()
{
	ll N=randint(1,5);
	ll B=randint(2,N+2);
	ll C=randint(2,N+2);
	vl A(N);
	FOR_E(a,A)a=randint(1,10);

	OUT(N,B,C);
	OUT(A);
}
