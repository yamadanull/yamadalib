#include "../../template/template.hpp"
#include "../../misc/all.hpp"

void yamada::solve()
{
	ll H=randint(1,10);
	ll W=randint(1,10);
	ll N=randint(1,20);
	vp ab;
	rep(N){
		ll a=randint(0,H);
		ll b=randint(0,W);
		ab.eb(a,b);
	}
	ab=mkuni(ab);
	N=ab.size();

	out(H,W,N);
	each2(a,b,ab)out(a+1,b+1);
}
