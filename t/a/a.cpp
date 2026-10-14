#include "../../template/template.hpp"
using namespace yamada;

void tc()
{
	inl(N);
	vl A(N); in(A);
	ll cnt=0;
	each(a,A)if(a<0)++cnt;
	if(N%2)die("NO");
	YESNO((N/2)%2==cnt%2);
}
void yamada::solve() { inl(T); while(T--)tc(); }
