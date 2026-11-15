#include "../../template/template.hpp"

void yamada::solve()
{
	IN(N,A=LL*N);
	vl ans(3);
	rep(i,N-1){
		if(A[i]<A[i+1])ans[0]++;
		else if(A[i]==A[i+1])ans[2]++;
		else ans[1]++;
	}
	out(ans);
}
