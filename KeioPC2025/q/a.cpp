#include "../../template/template.hpp"
using namespace yamada;

void tc()
{
	inl(N,M);
	if(M==1)die(N);
	if(M==2){
		auto check=[&](ll k)->bool{
			i128 ans=(i128)(k+1)*k/2;
			return ans<N;
		};
		die(bisect(0LL,infLL,check));
	}

	i128 c=1;
	rep(k,1,infLL){
		/* out(M+k-1,M,":",c); */
		if(c>=N)die(k);
		c*=M+k;
		c/=k;
	}
}
void yamada::solve() { ini(T); while(T--)tc(); }
