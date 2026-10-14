#include "../../template/template.hpp"
#include "../../internal/internal-math.hpp"
#include "../../multiplicative-function/divisor-multiple-transform.hpp"
#include "../../prime/fast-factorize.hpp"
#include "../../modint/montgomery-modint.hpp"
using namespace yamada;

using mint = LazyMontgomeryModInt<998244353>;
mint cal(ll N,ll A,ll B,ll X){
	if(X==0){
		mint ans=A+B;
		ans+=(mint)A*N+B;
		ans*=N;
		ans/=2;
		return ans;
	}

	auto pcA=factor_count(A);

	map<ll,ll> mp;
	each(d,divisors(X)){
		ll r,m;
		{
			vl rem{0,modulo(-B,d)};
			vl mod{A,d};
			tie(r,m)=internal::crt(rem,mod);
		}
		if(m==0)continue;

		ll lim=N*A;
		if(r!=0)lim+=m-r;
		mp[d]=lim/m;
	}

	multiple_transform::mobius_transform(mp);

	mint ans=0;
	each2(d,bns,mp){
		ans+=(mint)d*bns;
	}
	return ans;
}

mint cal(ll N,ll A,ll B,ll C,ll D){
	if(A<C)return cal(N,C,D,A,B);
	if(C==0)return cal(N,A,B,abs(D));

	// A>=C
	ll cof=A/C;
	A-=cof*C;
	B-=cof*D;
	return cal(N,A,B,C,D);
}

void yamada::solve()
{
	inl(Q);
	while(Q--){
		inl(N,A,B,C,D);
		out(cal(N,A,B,C,D));
	}
}
