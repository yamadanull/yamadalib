#include "../../template/template.hpp"
using namespace yamada;

void tc()
{
	inl(N);
	vl A(N),B(N); in(A,B);
	if(A==B)die(0);
	{
		bool fn=0;
		each(b,B)if(!b)fn=1;
		if(!fn)die(-1);
	}
	{
		bool fn=0;
		each(a,A)if(a)fn=1;
		if(!fn)die(-1);
	}

	ll cnt=0;
	rep(i,N)if(A[i]==1 && B[i]==0)++cnt;
	if(cnt%2)die(1);
	out(2);
}
void yamada::solve() { ini(T); while(T--)tc(); }
