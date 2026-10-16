#include "../../template/template.hpp"
#include "../../misc/all.hpp"

void yamada::solve()
{
	ll TC=100;
	out(TC);
	rep(TC){
		ll N=randint(6,11);
		ll K=randint(1,N+1);
		auto A=mkiota(N);
		randshf(A);

		out(N,K);
		out(A|Ofs());
	}
}
