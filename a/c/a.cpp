#include "../../template/template.hpp"
#include "../../prime/prime-enumerate.hpp"

void yamada::solve()
{
	auto PS=prime_enumerate(1<<18);
	IN(T);
	while(T--){
		IN(N,A=LL*N);
		each(a,A)a=*LowerBound(PS,a);
		out(A);
	}
}
