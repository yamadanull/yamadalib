#include "../../template/template.hpp"
using namespace yamada;

void tc()
{
	inl(N,M,K);
	assert(K<500);
	vl A(N),B(M),C(K); in(A,B,C);
	each(a,A)--a;
	each(a,B)--a;
	each(a,C)--a;

	vl ans(K,infLL);
	rep(sta,K-N+1)rep(stb,K-M+1){
		vl bns(K,-1);
		{
			bool fn=1;
			rep(i,N){
				bns[i+sta]=A[i];
			}
			rep(j,M){
				if(bns[j+stb]>=0 && bns[j+stb]!=B[j]){
					fn=0;
					break;
				}
				bns[j+stb]=B[j];
			}
			if(!fn)continue;
		}

		vl cnt(K);
		each(c,C)++cnt[c];
		each(a,bns)if(a>=0)--cnt[a];

		{
			bool fn=1;
			each(c,cnt)if(c<0){
				fn=0;
				break;
			}
			if(!fn)continue;
		}

		vl Q;
		repr(i,K)rep(cnt[i])Q.eb(i);
		each(a,bns)if(a<0){
			a=Q.back();
			Q.pop_back();
		}
		assert(Q.empty());
		amin(ans,bns);
	}

	if(ans[0]==infLL)out(-1);
	else{
		each(a,ans)++a;
		out(ans);
	}
}
void yamada::solve() { ini(T); while(T--)tc(); }
