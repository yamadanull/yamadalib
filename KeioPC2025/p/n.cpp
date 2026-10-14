#include "../../template/template.hpp"
#include "../../misc/int_div.hpp"
using namespace yamada;

bool is_ari(vl A){
	ll N=A.size();
	if(N<=2)return 1;
	sort(all(A));
	ll MD=A[1]-A[0];
	rep(i,N-1)if(A[i+1]-A[i]!=MD)return 0;
	return 1;
}

void tc()
{
	inl(N);
	vl A(N); in(A);
	ll ans=infLL;
	rep(msk,1<<N){
		auto B=A;
		rep(i,N)if(msk>>i&1)B[i]*=-1;
		if(is_ari(B))amin(ans,popcnt(msk));
	}
	if(ans==infLL)out(-1);
	else out(ans);
}
void yamada::solve() { ini(T); while(T--)tc(); }
