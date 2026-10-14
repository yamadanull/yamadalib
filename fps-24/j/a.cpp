#include "../../template/template.hpp"
#include "../../ntt/relaxed-convolution.hpp"
#include "../../fps/ntt-friendly-fps.hpp"
#include "../../modint/montgomery-modint.hpp"

using mint = LazyMontgomeryModInt<998244353>;
using fps = FormalPowerSeries<mint>;
void yamada::solve()
{
	inl(N,M,L);
	fps A(N+1);
	rep(M){
		inl(ai);
		A[ai]=((mint)1)/M;
	}
	V<bool> B(N+1);
	rep(L){
		inl(bi);
		B[bi]=1;
	}

	// マスiにいた事のある確率
	auto F=(-A+1).inv();

	// 初地雷がマスiである確率
	fps G(N+1);
	// 今までに地雷を踏んでなおかつマスiにいる確率
	RelaxedConvolution<fps> rc(N+1);
	mint ans=1;
	rep(i,N+1){
		if(B[i]){
			G[i]=F[i];
			G[i]-=rc.c[i];
			ans-=G[i];
		}
		rc.get(F[i],G[i]);
	}
	/* out(G); */
	out(ans);
}
