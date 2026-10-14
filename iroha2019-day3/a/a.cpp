#include "../../template/template.hpp"
#include "../../modint/arbitrary-modint.hpp"
#include "../../prime/fast-factorize.hpp"

using mint=ArbitraryModInt;
void yamada::solve()
{
	mint::set_mod(9973);
	{
		inl(a,b);
		out(a-b);
	}
	{
		inl(c,d);
		out(c+d);
	}
	{
		inl(e,f);
		out(max(0LL,f-e+1));
	}
	{
		inl(g,h,i);
		out((g+h+i+3)/3);
	}
	{
		string S="dagabaji";
		ll N=S.size();
		inl(J);

		vs ans;
		auto dfs=[&](auto&& self,ll j,ll lim,string cur)->void{
			if(j==0){
				ans.eb(cur);
				return;
			}
			rep(i,lim,N){
				cur+=S[i];
				self(self,j-1,i+1,cur);
				cur.pop_back();
			}
		}; dfs(dfs,J,0,"");
		out(Min(ans));
	}
	{
		ll m1=59;
		ll m2=61;
		inl(x,y,z);
		vl ans;
		rep(i,x,infLL,m1){
			if(i%m2==y)ans.eb(i);
			if(ans.size()>=z)break;
		}
		inl(N);
		reverse(all(ans));
		while(ans.size()>=2)ans.pop_back();
		vl A{6,28,496,8128,33550336,8589869056};
		each(a,A)if(abs(ans.back()-a)>=N){
			ans.eb(a);
			break;
		}
		sort(all(ans));
		each(a,ans)out(a);
	}
	{
		ll N=4,M=3;
		vv(ll,A,N,M); in(A);
		mint ans=1;
		rep(i,N){
			mint bns=0;
			rep(j,M){
				bns+=A[i][j];
			}
			ans*=bns;
		}
		out(ans);
	}
}
