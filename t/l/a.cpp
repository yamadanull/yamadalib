#include "../../template/template.hpp"

void yamada::solve()
{
	inl(N,P);
	vl A(N); in(A);
	vl B;
	rep(i,N){
		if(i+A[i]<N-1);
		else if(i+A[i]>P);
		else B.eb(A[i]+i);
	}
	each(b,B)b*=-1;

	vl dp;
	dp.eb(-P);
	each(b,B){
		ll pos=ub(dp,b);
		if(pos==dp.size())dp.eb(b);
		else dp[pos]=b;
	}
	/* out(dp); */
	out(N+1-(ll)dp.size());
}
