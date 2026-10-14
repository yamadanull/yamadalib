#include "../../template/template.hpp"
#include "../../modint/montgomery-modint.hpp"
using namespace yamada;

using mint = LazyMontgomeryModInt<998244353>;
void tc()
{
	inl(N);
	vl A(N); in(A); each(a,A)--a;
	mint ans=0;
	rep(i,N){
		if(i==N-1)ans+=1;
		if(A[i]==i){
			ans+=max(N-i-1,0LL);
		}
		else break;
	}
	out(ans);
}
void yamada::solve() { ini(T); while(T--)tc(); }
