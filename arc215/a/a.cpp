#include "../../template/template.hpp"
using namespace yamada;

void tc()
{
	inl(N,K,X);
	vl A(N); in(A); sort(all(A));
	vp Bi;
	rep(i,N-1)Bi.eb(A[i+1]-A[i],i);
	sort(all(Bi)); reverse(all(Bi));

	ll L=A[0];
	ll R=X-A.back();

	ll ans=-infLL;
	ll bns=0;
	rep(i,min(N,K+1)){
		ll rem=K-i;
		ll cns=bns;
		if(rem>0){
			cns+=max(L,R);
			cns+=(L+R)*(rem-1);
		}
		amax(ans,cns);
		if(i<N-1){
			auto[b,ai]=Bi[i];
			L+=b/2;
			R+=b/2;
			bns+=b/2;
		}
	}
	out(ans);
}
void yamada::solve() { ini(T); while(T--)tc(); }
