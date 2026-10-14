#include "../../template/template.hpp"
#include "../../fps/ntt-friendly-fps.hpp"
#include "../../modint/montgomery-modint.hpp"

using mint = LazyMontgomeryModInt<998244353>;
using fps = FormalPowerSeries<mint>;
void yamada::solve()
{
	inl(log,T,X); --X; ++log;
	ll N=1LL<<log;
	// N乗根のi乗
	V<mint> pw(N,1);
	V<mint> iv(N,1);
	{
		// 周期
		ll t=mint::get_mod()-1;
		t/=N;

		mint r=((mint)3).pow(t);
		mint rinv=r.inverse();
		rep(i,N){
			pw[i+1]=pw[i]*r;
			iv[i+1]=iv[i]*rinv;
		}
	}

	auto fft=[&](auto&& self,fps &F,ll dep,bool inv=false)->fps{
		if(dep==0)return F;
		ll n=1<<dep;
		fps F0(n/2);
		fps F1(n/2);
		rep(i,n)(i%2? F1:F0)[i/2]=F[i];
		auto _F0=self(self,F0,dep-1,inv);
		auto _F1=self(self,F1,dep-1,inv);
		fps ans(n);
		rep(k,n)ans[k]=_F0[k%(n/2)]+_F1[k%(n/2)]*(inv? iv:pw)[k*(N/n)];
		return ans;
	};

	fps F(N);
	F[1]=F.back()=((mint)2).inverse();

	fps F2=fft(fft,F,log,false);
	each(f,F2)f=f.pow(T);
	fps F3=fft(fft,F2,log,true);

	mint ans=F3[X];
	if(X%(N/2))ans+=F3[N-X];
	out(ans/N);
}
