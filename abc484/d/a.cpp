#include "../../template/template.hpp"
#include "../../data-structure-2d/wavelet-matrix.hpp"

void yamada::solve()
{
	IN(N,A=LL*N);
	vl B(N);
	for(ll l=0,r=0;l<N;l=r){
		while(r<N&&A[l]==A[r])++r;
		B[l]=A[l];
	}
	ll ans=0; // ZZ
	WaveletMatrix<ll> wm(B);
	rep(i,N){
		ans+=wm.range_freq(i+1,N,1,N+1);
		ans-=wm.range_freq(i+1,N,A[i],A[i]+1);
		/* err(ans); */
	}
	out(ans+1);
}
