#include "../../template/template.hpp"
#include "../../fps/ntt-friendly-fps.hpp"
#include "../../modulo/binomial.hpp"
#include "../../modint/montgomery-modint.hpp"

void yamada::solve()
{
	using mint = LazyMontgomeryModInt<998244353>;
	using fps = FormalPowerSeries<mint>;
	Binomial<mint> binom;

	inl(N); ll M=1<<17;
	vl B(N),S(N); in(B,S); repr(i,1,N)S[i]=S[i-1];

	// ゼッケン番号の差がiであるペアの数
	fps cnt(M);
	{
		fps dnt(M); each(b,B)dnt[b]+=1;
		fps ent=dnt;
		reverse(all(ent));
		ent*=dnt;
		rep(i,M,ent.size())cnt[i-M+1]=ent[i];
	}

	mint ans=0;
	rep(i,1,N){
		mint bns=S[i];
		bns*=cnt[i];
		bns*=N-i;
		bns*=binom.fac(N-2);
		ans+=bns;
	}
	out(ans);
}
