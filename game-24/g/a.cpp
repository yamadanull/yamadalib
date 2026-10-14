#include "../../template/multitest-template.hpp"

void yamada::solve()
{
	inl(N);
	ll ans=infLL;
	rep(N){
		inl(a,b);
		auto[quo,rem]=divmod(a,b+1);
		ll bns=quo*2+min<ll>(rem,1);
		amin(ans,bns);
	}
	out(ans%2?"Alice":"Bob");
}
