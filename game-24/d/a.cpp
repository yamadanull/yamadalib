#include "../../template/multitest-template.hpp"

void yamada::solve()
{
	inl(N);
	bool ans=0;
	rep(N){
		inl(a,b);
		if(a%(b+1))ans=1;
	}
	out(ans?"Alice":"Bob");
}
