#include "../../template/template.hpp"
#include "../../modint/montgomery-modint.hpp"

using mint = LazyMontgomeryModInt<998244353>;
void yamada::solve()
{
	inl(N,M);
	if(M>=2)die(0);
	mint inv10=((mint)1)/10;

	mint ans=1;
	ans-=inv10.pow(N);
	ans/=9;
	ans*=10;

	mint bns=0;
	bns+=((mint)10).pow(N)-1;
	bns/=9;
	/* out(ans,bns); */

	mint X=(ans*((mint)10).pow(N*2)-bns)*5/11;
	mint Y=(((mint)10).pow(N)-1)*5;
	X-=Y;
	out(X*9/10+Y);
}
