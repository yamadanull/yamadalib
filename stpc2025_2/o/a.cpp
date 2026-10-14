#include "../../template/template.hpp"

void yamada::solve()
{
	inl(N,L,W);
	map<ll,bool> ng;
	rep(i,N){
		inl(d);
		ng[d]=true;
	}

	L=(L+W-1)/W*W;
	rep(x,L,infLL,W){
		if(!ng.count(x))die(x);
	}
}
