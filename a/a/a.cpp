#include "../../template/multitest-template.hpp"
 
void yamada::solve()
{
	IN(N,S=STR);
	ll cnt=0;
	each(c,S)if(c=='1')++cnt;
	if(cnt==1)DIE(0);
	if(cnt==2)DIE(1);
	ll mn=infLL,mx=-infLL;
	each(i,c,S|Enumerate)if(c=='1'){
		amin(mn,i);
		amax(mx,i);
	}
	out(mx-mn);
}
