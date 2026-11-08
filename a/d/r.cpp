#include "../../template/template.hpp"
#include "../../misc/random-graph.hpp"
#include "../../misc/all.hpp"

void yamada::solve()
{
	ll T=2;
	out(T);
	while(T--){
		ll N=randint(2,6);
		ll M=randint(N-1,N*(N-1)/2);
		auto g=randgraph(N,M);
		vl A(4);
		each(a,A)a=randint(1,N+1);

		out(N,M);
		out(A);
		print_edge(g);
	}
}
