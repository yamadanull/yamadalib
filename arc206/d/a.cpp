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
			if(N>=5){
				vl ans={1,4,2,0,3};
				rep(i,5,N)ans.eb(i);
				each(a,ans)++a;
				out(ans);
			}
			else if(N==1){
				out(1);
			}
			else out(-1);
		}
		else{
			if(N>=8){
				vl ans={2,3,7,6,1,0,4,5};
				rep(i,8,N)ans.eb(i);
				each(a,ans)++a;
				out(ans);
			}
			else out(-1);
		}
	}
}
