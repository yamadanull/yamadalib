#include "../../template/template.hpp"
#include "../../modint/montgomery-modint.hpp"
using namespace yamada;

using mint = LazyMontgomeryModInt<998244353>;
void tc()
{
	inl(N);
	vl A(N); in(A); each(a,A)--a;
	vl B(N); rep(i,N)B[i]=i;

	mint ans=0;
	do{
		vl C(N,infLL);
		rep(l,N)rep(r,l+1,N+1){
			reverse(B.begin()+l,B.begin()+r);
			amin(C,B);
			reverse(B.begin()+l,B.begin()+r);
		}
		if(C==A)ans+=1;
	}while(nxp(B));
	out(ans);
}
void yamada::solve() { ini(T); while(T--)tc(); }
