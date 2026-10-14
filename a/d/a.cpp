#include "../../template/multitest-template.hpp"
#include "../../segment-tree/lazy-segment-tree-utility.hpp"

void yamada::solve()
{
	IN(N,A=--LL*N,B=--LL*N);
	vint to(N);
	{
		vl cnt(N),dnt(N);
		each(a,A)++cnt[a];
		each(b,B)++dnt[b];
		if(cnt!=dnt)DIE("NO");
		vvl pos(N),qos(N);
		rep(i,N)pos[A[i]].eb(i);
		rep(i,N)qos[B[i]].eb(i);
		rep(a,N){
			each(i,j,Zip(pos[a],qos[a]))to[i]=j;
		}
	}

	auto toinv=mkinv(to);
	max_segtree<ll> seg(vl(N,-1));
	each(i,toinv){
		seg.set(i,A[i]);
		if(A[i]<=seg(i+1,N))DIE("NO");
	}
	out("YES");
}
