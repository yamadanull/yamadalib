#include "../../template/multitest-template.hpp"

void yamada::solve()
{
	IN(S=STR);
	set<ll> diff{0};
	ll N=len(S);
	rep(i,1,N-1){
		if(S[i-1]!=S[i+1])diff.insert(0);
		else{
			if(S[i-1]==S[i])diff.insert(1);
			else diff.insert(-1);
		}
	}
	out(len(diff));
}
