#include "../../template/multitest-template.hpp"

void yamada::solve()
{
	IN(N,A=LL*N);
	if(Max(A)==1)DIE(-1);
	if(N>=3 && Max(A|Drop(1)|Take(N-2))==1){
		DIE(Sum(A)-N+1);
	}
	out(Sum(A)-1);
}
