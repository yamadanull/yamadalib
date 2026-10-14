#include "../../template/template.hpp"
using namespace yamada;

ll cal(vl A){
	ll N=A.size();
	// sita,sitenai
	vl dp(N+1,-infLL),ep(N+1,-infLL);
	dp[0]=ep[0]=0;
	rep(i,N){
		amax(ep[i+1],dp[i]);
		amax(ep[i+1],ep[i]);
		amax(dp[i+1],ep[i]+A[i]);
	}
	return max(dp[N],ep[N]);
}

void yamada::solve()
{
	inl(N,Q);
	vl A(N); in(A);
	while(Q--){
		inl(k,x); --k;
		A[k]=x;
		out(cal(A));
	}
}
