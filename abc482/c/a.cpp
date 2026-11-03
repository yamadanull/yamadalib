#include "../../template/template.hpp"

void yamada::solve()
{
	IN(H,W,N,Q,RC=PR(LL,LL)*N);
	vl cmpr,cmpc;
	each(r,c,RC){
		cmpr.eb(r);
		cmpc.eb(c);
	}
	cmpr=mkuni(cmpr);
	cmpc=mkuni(cmpc);
	ll h=len(cmpr);
	ll w=len(cmpc);
	vl cntr(h),cntc(w);
	each(r,c,RC){
		cntr[lb(cmpr,r)]++;
		cntc[lb(cmpc,c)]++;
	}
	CumulativeSum cumr(cntr);
	CumulativeSum cumc(cntc);

	while(Q--){
		IN(op,L,R=++LL);
		if(op==1){
			L=lb(cmpr,L);
			R=lb(cmpr,R);
			out(cumr(L,R));
		}
		else{
			L=lb(cmpc,L);
			R=lb(cmpc,R);
			out(cumc(L,R));
		}
	}
}
