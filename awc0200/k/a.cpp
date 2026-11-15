#include "../../template/template.hpp"
#include "../../tree/cartesian-tree.hpp"

void yamada::solve()
{
	IN(N,S,A=LL*N);
	ll ans=infLL;
	CartesianTree ct(A);
	rep(i,N){
		auto[L,R]=ct.range[i];
		err(L,R);
		if((R-L)*A[i]>=S){
			ll bns=(S+A[i]-1)/A[i];
			amin(ans,bns);
		}
	}
	out(ans==infLL?-1:ans);
}
