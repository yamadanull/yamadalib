#include "../../template/multitest-template.hpp"

void yamada::solve()
{
	IN(N,A=LL*N);
	auto F=[&](ll a)->ll{
		if(a<0)return infLL;
		if(a==0)return 1;
		ll ans=0;
		rep(t,msb(a))if(!(a>>t&1))++ans;
		return ans;
	};
	auto check=[&](ll L)->bool{
		rep(i,N)if(F(L+i)!=A[i])return 0;
		return 1;
	};
	const int M=1<<13;
	rep(i,M){
		if(check(i))DIE(i);
	}
	out(-1);
}
