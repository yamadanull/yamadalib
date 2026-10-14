#include "../../template/template.hpp"

void yamada::solve()
{
	inl(N);
	const ll K=2019;
	vl cnt(K);
	vl pos(N); in(pos); each(p,pos)--p;
	each(p,pos)++cnt[p];

	inl(Q);
	while(Q--){
		inl(i); --i;
		if(pos[i]==K-1 || cnt[pos[i]+1]>=1);
		else{
			--cnt[pos[i]];
			++cnt[++pos[i]];
		}
	}

	each(p,pos)out(p+1);
}
