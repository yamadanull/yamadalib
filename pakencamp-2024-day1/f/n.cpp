#include "../../template/template.hpp"

void yamada::solve()
{
	inl(X);
	rep(N,1,X)if(X%N==0){
		vp es;
		rep(i,N)rep(j,i+1,N)es.eb(i,j);

		rep(S,1<<es.size()){
			vl cnt(N);
			rep(i,es.size())if(S>>i&1){
				auto[u,v]=es[i];
				++cnt[u];
				++cnt[v];
			}

			ll x=N;
			each(c,cnt)x*=c;
			if(x==X){
				out(N);
				rep(i,es.size())if(S>>i&1)out(es[i]);
				cout.flush();
			}
		}
	}
}
