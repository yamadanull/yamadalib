#include "../../template/template.hpp"

void yamada::solve()
{
	inl(N);
	vl A(N),B(N); in(A,B);
	rep(i,N){
		if(A[i]>B[i]){
			out("Yes");
			vl ans(N,1);
			ans[i]=1e18;
			out(ans);
			return;
		}
	}
	out("No");
}
