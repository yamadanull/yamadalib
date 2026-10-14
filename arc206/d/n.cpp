#include "../../template/template.hpp"

void yamada::solve()
{
	inl(TC);
	while(TC--)
	{
		inl(N,K);
		if(K>=2){
			vl ans(N);
			rep(i,K)ans[i]=K-i-1;
			rep(i,K,N)ans[i]=i;
			each(a,ans)++a;
			out(ans);
		}
		else if(K==1){
			if(N==1){
				out(1);
			}
			else out(-1);
		}
		else{
			out(-1);
		}
	}
}
