#include "../../template/multitest-template.hpp"

void yamada::solve()
{
	IN(N);
	VV(ll,ans,N,N);
	rep(i,N)rep(j,N)ans[i][j]=gcd(i+1,j+1);
	each(a,ans)out(a);
}
