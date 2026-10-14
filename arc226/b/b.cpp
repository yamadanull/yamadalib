#include "../../template/multitest-template.hpp"

constexpr int LG=61;
void yamada::solve()
{
	inl(N,M);
	vl A(LG);
	rep(t,M)in(A[t]);
	rep(t,LG)if(A[t]>N){
		assert(t!=LG-1);
		ll quo=A[t]/N;
		ll mod=A[t]%N;
		if(quo%2==0){
			A[t]=mod;
			A[t+1]+=quo/2*N;
		}
		else{
			A[t]=N-mod;
			A[t+1]+=(quo-1)/2*N+mod;
		}
	}
	/* out("A:",A); */

	ll ans=0;
	ll len=N; // 最大値を担っている場所の数
	repr(t,LG){
		if(A[t]+len<=N);
		else{
			ans+=1LL<<t;
			amin(len,A[t]+len-N);
		}
	}
	out(ans);
}
