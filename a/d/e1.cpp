#include "../../template/multitest-template.hpp"

void yamada::solve()
{
	inl(N,X,B);

	VV<bool> cur;
	auto dfs=[&](auto&& self)->void{
		if(cur.size()==N){
			rep(j,N){
				ll cnt=0;
				rep(i,N)cnt+=cur[i][j];
				if(cnt!=X)return;
			}
			rep(i,N-1)rep(j,N-1){
				bool b=0;
				rep(I,i,i+2)rep(J,j,j+2){
					b^=cur[I][J];
				}
				if(b!=B)return;
			}
			vs ans(N);
			rep(i,N)rep(j,N)ans[i]+=cur[i][j]? '#':'.';
			each(a,ans)out(a);
			out();
			return;
		}

		rep(msk,1<<N)if(popcnt(msk)==X){
			vc<bool> dur(N);
			rep(i,N)if(msk>>i&1)dur[i]=1;
			cur.eb(dur);
			self(self);
			cur.pop_back();
		}
	};
	dfs(dfs);
}
