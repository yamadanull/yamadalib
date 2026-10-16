#include "../../template/multitest-template.hpp"
#include "../../data-structure-2d/wavelet-matrix.hpp"

void yamada::solve()
{
	IN(N,K,A=LL*N);
	auto B=mkrui(A);
	each(b,B)b%=K;
	WaveletMatrix wm(B);
	err(B);
	ll ans=0;
	rep(i,N-K){
		ll rl=i+K+1;
		err(i,rl,B[i]);
		ans+=wm.range_freq(rl,N+1,B[i],B[i]+1);
	}
	out(ans);
}
