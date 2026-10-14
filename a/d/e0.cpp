#include "../../template/multitest-template.hpp"

void yamada::solve()
{
	inl(N,X);

	VV<int> cur;
	ll cnt=0;
	auto dfs=[&](auto&& self)->void{
		if(cur.size()==N){
			++cnt;
			bool fn=1;
			rep(i,N-1)rep(j,N-1){
				ll x=0;
				rep(I,i,i+2)rep(J,j,j+2){
					x^=cur[I][J];
				}
				if(x!=X)fn=0;
			}
			if(fn){
				vs ans(N);
				rep(i,N)each(a,cur[i]){
					if(a%2)ans[i]+='#';
					else ans[i]+='.';
				}
				each(s,ans)out(s);
				/* each(a,cur)out(a); */
				fout();
			}
			return;
		}

		auto p=mkiota(N);
		do{
			bool fn=1;
			rep(i,cur.size()){
				rep(j,N)if(p[j]==cur[i][j]){
					fn=0;
					break;
				}
				if(!fn)break;
			}
			if(fn){
				cur.eb(p);
				self(self);
				cur.pop_back();
			}
		}while(nxp(p));
	};
	dfs(dfs);
	fout("cnt:",cnt);
}
