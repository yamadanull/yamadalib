#include "../../template/template.hpp"
#include "../../enumerate/sequences.hpp"
using namespace yamada;

map<tuple<vc<int>,ll,bool>,bool> memo;
bool naive(vc<int> A,ll K,bool alice){
	if(memo.count(mkt(A,K,alice)))return memo[mkt(A,K,alice)];
	ll N=len(A);
	if(alice){
		each(i,a,A|enumerate)rep(b,a)if(a-b<=K){
			auto B=A;
			B[i]=b;
			if(!naive(B,K,!alice))return memo[mkt(A,K,alice)]=1;
		}
		return memo[mkt(A,K,alice)]=0;
	}
	else{
		rep(msk,1,1<<N)if(popcnt(msk)<=K){
			auto B=A;
			rep(i,N)if(msk>>i&1)--B[i];
			if(Min(B)<0)continue;
			if(!naive(B,K,!alice))return memo[mkt(A,K,alice)]=1;
		}
		return memo[mkt(A,K,alice)]=0;
	}
}

void yamada::solve()
{
	inl(N);
	/* rep(n,2,N+1)rep(k,1,N+1){ */
	/* 	err(n,k,naive(vc<int>(n,n-1),k,1)); */
	/* } */
	rep(k,1,N+1){
		err();
		auto F=[&](auto A){
			auto ans=naive(A,k,1);
			err(k,A,ans);
		};
		LengthFixedSequences(N,false,0,N,F);
	}
}
