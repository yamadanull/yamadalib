#include "../../template/template.hpp"
#include "../../modint/arbitrary-modint.hpp"
#include "../../dp/inversion-counting.hpp"
using namespace yamada;

using mint=ArbitraryModInt;
void tc()
{
	inl(N);
	mint::set_mod(N);
	vl A(N); in(A);
	sort(all(A));
	each(a,A)a%=N;

	if(mkuni(A).size()<N)die(0);

	mint ans=1;
	rep(i,1,N){
		ans*=mint(i).pow(N-i);
	}
	if(inversion_counting(A)%2)ans*=-1;
	out(ans);
}
void yamada::solve() { ini(T); while(T--)tc(); }
