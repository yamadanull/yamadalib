#include "../../template/template.hpp"
#include "../../misc/random-graph.hpp"
#include "../../misc/all.hpp"

constexpr int LG=1;
void yamada::solve()
{
	out(1);
	ll N=1e5;
	ll Q=1e5;
	auto g=randtree(N);
	vl A(N);
	each(a,A)a=randint(0,1<<LG);

	out(N,Q);
	out(A);
	print_edge(g);

	while(Q--){
		ll u=randint(0,N-1);
		ll v=randint(u+1,N);
		out(u+1,v+1);
	}
}
