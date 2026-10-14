#include "../../template/template.hpp"
#include "../../misc/all.hpp"

void yamada::solve()
{
	int T = 10000;
	cout << T << "\n";
	while (T--) {
		ll N=randint(2,10);
		ll M=randint(1,10);
		vp lr(M);
		FOR_E(l,r,lr){
			l=randint(0,N-1);
			r=randint(l+2,N+1);
		}

		OUT(N,M);
		FOR_E(l,r,lr)OUT(l+1,r);
	}
}
