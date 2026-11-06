#include "../../template/multitest-template.hpp"
using namespace yamada;

void exper(){
	IN(N);
	auto A=mkiota(N)|Ofs(1)|rtov;
	err(A);
	ll K=0; each(a,A)K|=a;
	rep(msk,1<<N){
		ll M=0;
		rep(i,N){
			if(msk>>i&1)M^=A[i]*2;
			else M^=A[i];
		}
		if(M>=K*2+1)fout(tog(msk,N));
	}
}

void yamada::solve()
{
	exper();
}
