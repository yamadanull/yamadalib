#include "../../template/multitest-template.hpp"
#include "../../segment-tree/lazy-segment-tree-utility.hpp"

const int BS=10;
void yamada::solve()
{
	IN(N,S=STR);
	each(c,S)c-='0';
	vvl pos(BS);
	each(i,c,S|Enumerate)pos[c].eb(i);
	VV(ll,A,BS,N,N);
	rep(d,BS)rep(i,N){
		ll pi=lb(pos[d],i);
		if(pi<len(pos[d])){
			ll j=pos[d][pi];
			A[d][i]=j;
		}
	}

	addmax_lazyseg<i128> seg0(vc<i128>(N,0));
	addmax_lazyseg<i128> seg1(vc<i128>(N,0));
	rep(l,N){
		ll u=l;
		u=A[2][u];
		if(u==N)continue;
		u=A[0][u];
		if(u==N)continue;
		u=A[2][u];
		if(u==N)continue;
		ll L=A[5][u];
		ll R=A[6][u];
		if(L>=R)continue;
		err(l,L,R);
		seg0.apply(l,L,R-L);
		seg0.apply(L,R,R);
		seg1.apply(L,R,-1);
	}

	vc<i128> ans(N);
	rep(i,N)ans[i]=(i+1)*(N-i)-(seg0[i]+seg1[i]*i);
	out(ans);
}
