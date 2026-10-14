#include "../../template/template.hpp"
#include "../../modint/montgomery-modint.hpp"

using mint = LazyMontgomeryModInt<998244353>;
int cnt[500][250'000];
void yamada::solve()
{
	ini(N,M);
	vv(int,A,N,M); in(A);
	each(v,A)each(a,v)--a;

	rep(i,N)rep(j,M)cnt[i][A[i][j]]++;
	mint ans=0;
	rep(i,N)rep(j,M){
		// この数が何回寄与するか
		mint bns=1;
		ll a=A[i][j];
		rep(I,i){
			bns*=M-cnt[I][a];
		}
		bns*=((mint)M).pow(N-i-1);
		ans+=bns;
	}
	out(ans);
}
