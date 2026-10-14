#include "../../template/template.hpp"
using namespace yamada;

void tc()
{
	inl(N,K);
	vv(ll,A,N,N); in(A);
	ll ans=0;
	rep(i,N)rep(j,N)if(i%2!=j%2){
		ans^=A[i][j]%(K+1);
	}
	out(ans? "Alice":"Bob");
}
void yamada::solve() { ini(T); while(T--)tc(); }
