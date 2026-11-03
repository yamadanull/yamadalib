#include "../../template/multitest-template.hpp"

void yamada::solve()
{
	IN(N,A=LL*N);
	each(a,A|Stride(2))a*=-1;
	Sort(A);
	out(Sum(A|Drop(N+1>>1))-Sum(A|Take(N+1>>1)));
}
