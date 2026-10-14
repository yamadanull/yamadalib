#include "../../template/template.hpp"

void yamada::solve()
{
	inl(N);
	ll ans=0;
	rep(N){
		inl(a);
		ans^=a;
	}
	out(ans?"Alice":"Bob");
}
