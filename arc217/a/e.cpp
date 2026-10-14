#include "../../template/template.hpp"

void yamada::solve()
{
	inl(N);
	vl A(N);
	rep(i,N)A[i]=i+1;
	ll ans=infLL;
	do{
		auto B=A;
		rep(i,1,N)B[i]^=B[i-1];
		amin(ans,Sum(B));
	}while(nxp(A));
	do{
		auto B=A;
		rep(i,1,N)B[i]^=B[i-1];
		if(Sum(B)==ans){
			out(A);
		}
	}while(nxp(A));
}
