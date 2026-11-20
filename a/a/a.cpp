#include "../../template/template.hpp"
#include "../../segment-tree/lazy-segment-tree-utility.hpp"

void yamada::solve()
{
	IN(N,T,BIND(A,B)=~PR(--LL,LL)[N]);
	Sort(Zip(B,A));
	sum_segtree<ll> segsum(B); // 予約問題は零
	sum_segtree<ll> segcnt(vl(N,1));
	err(A);
	err(B);

	vl vis(N);
	ll pos=0; // 最後に追加した予約問題
	ll ans=0;
	rep(m,1,N+1){
		while(pos<N&&vis[A[pos]])++pos;
		if(pos>=N)break;
		vis[A[pos]]=1;
		segsum.set(pos,0);
		segcnt.set(pos,0);
		T-=B[pos];
		++pos;
		if(T<0)break;
		ll R=segsum.max_right(0,[&](ll sm){return sm<=T;});
		ll bns=segcnt(0,R)+m*2;
		err();
		err(m,T,R,bns);
		err(segsum.get());
		err(segcnt.get());
		amax(ans,bns);
	}
	out(ans);
}
