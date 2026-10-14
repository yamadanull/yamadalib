#include "../../template/template.hpp"
#include "../../modint/montgomery-modint.hpp"

using mint = LazyMontgomeryModInt<998244353>;
void yamada::solve()
{
	inl(N);
	vl A(N); in(A); each(a,A)if(a>0)--a;

	// 飛び出し頂点になりうるやつ
	ll L=0,R=N-1;
	{
		// 飛び出し頂点とその行き先が固定されているか
		bool fn=false;
		rep(i,N)if(A[i]>=0){
			if(A[i]==i+1){
				amax(L,i+1);
			}
			else if(A[i]==i-1){
				amin(R,i-1);
			}
			else{
				if(fn)die(0);
				amax(L,i);
				amin(R,i);
				fn=true;
			}
		}

		if(fn){
			if(L>R)die(0);
			die(1);
		}
	}

	if(R<=L-2)die(0);
	if(R==L-1)die(1);
	mint ans=(R-L+1)*N;
	ans-=R-L;
	out(ans);
}
