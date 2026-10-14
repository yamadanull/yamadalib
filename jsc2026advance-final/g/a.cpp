#include "../../template/multitest-template.hpp"

void yamada::solve()
{
	auto check=[&](ll N,ll M,ll K)->bool{
		if(N%2==0)return 0;
		if(M%2==0)return 0;
		ll R=(M-1)*(N+1)/2;
		ll L=M-1;
		if(K<L)return 0;
		if(K>R)return 0;
		if(K%2)return 0;
		return 1;
	};

	string ans;
	auto dfs=[&](auto&& self,ll N,ll M,ll K)->void{ // (N,M,K)の場合の動きをansに追加
		assert(check(N,M,K));
		if(N==1){
			rep(M-1)ans+='R';
			return;
		}
		if(M==1){
			rep(N-1)ans+='D';
			return;
		}

		if(check(N-2,M,K-(M-1))){
			rep(M-1)ans+='R';
			ans+='D';
			rep(M-1)ans+='L';
			ans+='D';
			self(self,N-2,M,K-(M-1));
			return;
		}

		assert(check(N,M-2,K-2));
		rep(N-1)ans+='D';
		ans+='R';
		rep(N-1)ans+='U';
		ans+='R';
		self(self,N,M-2,K-2);
	};

	inl(N,K);
	if(!YesNo(check(N,N,K)))return;
	dfs(dfs,N,N,K);
	out(ans);
}
