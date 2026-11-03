#include "../../template/multitest-template.hpp"

void yamada::solve()
{
	IN(N,A=LL*N);
	Sort(A);
	ll X=A[N/2];
	ll ans=0;
	each(a,A)ans+=abs(a-X);
	ll bns=A.back()-A.front();
	out(ans,bns);
}
