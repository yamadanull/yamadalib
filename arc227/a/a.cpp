#include "../../template/template.hpp"

void yamada::solve()
{
	inl(N);
	ll K=3;
	vs S(K); in(S);

	vvl pos(K);
	rep(k,K){
		rep(i,N*2)if(S[k][i]=='1')pos[k].eb(i);
	}

	pos=Transpose(pos);
	ll ans=0;
	string bns;
	rep(N*2)bns+='0';
	rep(i,N){
		sort(all(pos[i]));
		ll m=pos[i][1];
		rep(k,K)ans+=abs(pos[i][k]-m);
		bns[m]='1';
	}
	out(ans);
	out(bns);
}
