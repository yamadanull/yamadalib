#include "../../template/template.hpp"
#include "../../math/rational.hpp"

void yamada::solve()
{
	IN(N,S=CHR*N);
	ll cnt=0;
	each(c,S)if(c!=S[0])++cnt;
	Rational a(cnt,N-1);
	cout<<a.x<<"/"<<a.y<<endl;
}
