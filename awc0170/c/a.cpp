#include "../../template/template.hpp"

const int M=1<<19;
void yamada::solve()
{
	IN(N,A=LL*N);
	bitset<M> bs;
	bs.set(0);
	each(a,A){
		bs|=bs<<a;
	}
	ll sm=Sum(A);
	ll ans=infLL;
	rep(i,M)if(bs[i]){
		amin(ans,abs(sm-i*2));
	}
	out(ans);
}
