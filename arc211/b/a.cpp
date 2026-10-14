#include "../../template/template.hpp"
/* #include <ranges> */
/* using ranges::views::drop; */
/* using ranges::views::take; */

void yamada::solve()
{
	inl(x,y,z);
	vl ans,bns,cns;
	if(x==y){
		rep(x)ans.eb(0);
		rep(z)bns.eb(0);
		rep(z)cns.eb(0);
	}
	else{
		rep(y)ans.eb(0);
		rep(x)bns.eb(0);
		rep(z-x)bns.eb(1);
		rep(y)cns.eb(0);
		rep(z-x)cns.eb(1);
	}
	out(ans.size(),ans);
	out(bns.size(),bns);
	out(cns.size(),cns);
}
