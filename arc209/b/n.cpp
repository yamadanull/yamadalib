#include "../../template/template.hpp"

void yamada::solve()
{
	auto check=[](string S)->bool{
		ll N=S.size();
		rep(i,N/2)if(S[i]!=S[N-i-1])return false;
		return true;
	};
	auto count=[&](string S)->ll{
		ll N=S.size();
		ll ans=0;
		rep(i,N)rep(j,i+2,N+1,2){
			if(check(S.substr(i,j-i))){
				/* if(S=="xxxyxx")out(i,j); */
				++ans;
			}
		}
		return ans;
	};

	ins(S);
	ll N=S.size();
	ll M=26;
	vl cnt(M);
	each(c,S)cnt[c-'a']++;

	ll ans=infLL;
	auto dfs=[&](auto&& self,char C,vl vis)->void{
		if(C=='a'+M){
			string T;
			rep(i,N)T+=vis[i]+'a';
			amin(ans,count(T));
			return;
		}

		ll n=cnt[C-'a'];
		auto efs=[&](auto&& telf,ll id,ll L)->void{
			if(id==n){
				self(self,C+1,vis);
				return;
			}
			rep(i,L,N)if(vis[i]<0){
				vis[i]=C-'a';
				telf(telf,id+1,i+1);
				vis[i]=-1;
			}
		}; efs(efs,0,0);
	}; dfs(dfs,'a',vl(N,-1));

	out(ans);
	auto dfs2=[&](auto&& self,char C,vl vis)->void{
		if(C=='a'+M){
			string T;
			rep(i,N)T+=vis[i]+'a';
			if(ans==count(T))out(T);
			return;
		}

		ll n=cnt[C-'a'];
		auto efs2=[&](auto&& telf,ll id,ll L)->void{
			if(id==n){
				self(self,C+1,vis);
				return;
			}
			rep(i,L,N)if(vis[i]<0){
				vis[i]=C-'a';
				telf(telf,id+1,i+1);
				vis[i]=-1;
			}
		}; efs2(efs2,0,0);
	}; dfs2(dfs2,'a',vl(N,-1));
}
