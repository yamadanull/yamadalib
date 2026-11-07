#include "../../template/multitest-template.hpp"

void yamada::solve()
{
	IN(N,A=LL*N);
	Sort(A,greater{});
	ll cur=0;
	ll sm=0;
	each(a,A){
		if(cur<0)cur+=1LL<<a;
		else cur-=1LL<<a;
		sm+=1LL<<a;
	}
	ll x=(cur+sm)/2;
	ll y=sm-x;
	out(x*y);
}
