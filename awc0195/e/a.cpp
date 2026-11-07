#include "../../template/template.hpp"
#include "../../data-structure-2d/wavelet-matrix.hpp"

void yamada::solve()
{
	IN(N,X,Y,BIND(A,B)=~PR(LL,LL)[N]);
	Sort(Zip(A,B));
	WaveletMatrix wm(B);
	ll ans=0;
	rep(i,N){
		ll L=lb(A,X-A[i]);
		amax(L,i+1);
		ll D=Y-B[i];
		amax(D,0);
		ans+=wm.range_freq(L,N,D,MSK(30));
	}
	out(ans);
}
