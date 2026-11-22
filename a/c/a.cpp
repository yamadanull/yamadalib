#include "../../template/multitest-template.hpp"
#include "../../tree/cartesian-tree.hpp"

void yamada::solve()
{
	IN(N,A=--LL*N);
	CartesianTree ct(A);
	ll ans=0;
	rep(i,N){
		auto[l,r]=ct.range[i];
		if(i==l){
			ans+=r-i;
		}
		else if(r==i+1){
			ans+=i-l+1;
		}
		else{
			ans+=2;
		}
	}
	out(ans);
}
