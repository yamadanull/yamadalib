#include "../../template/multitest-template.hpp"
using namespace yamada;

// [count(Aのあまり)、(Bのあまり)、(素のC)、(素のD)]
map<array<ll,4>,bool> memo;
bool naive(array<ll,4> A){
	if(memo.count(A))return memo[A];
	auto flip=[&](auto& a){
		swap(a[0],a[1]);
		swap(a[2],a[3]);
	};
	if(A[1]){
		auto B=A;
		--B[1];
		flip(B);
		if(!naive(B))return memo[A]=1;
	}
	if(A[2]){
		auto B=A;
		--B[2];
		++B[0];
		flip(B);
		if(!naive(B))return memo[A]=1;
	}
	if(A[3]){ // 妨害する
		auto B=A;
		--B[3];
		flip(B);
		if(!naive(B))return memo[A]=1;
	}
	if(A[3]){ // 妨害しない
		auto B=A;
		--B[3];
		++B[0];
		flip(B);
		if(!naive(B))return memo[A]=1;
	}
	return memo[A]=0;
}
bool cal(ll a,ll b,ll c,ll d){
	ll ans=(b-a)*4+(d-c);
	return ans>0;
}

void exper(){
	inl(M);
	rep(a,M)rep(b,M)rep(c,M)rep(d,M){
		auto ans=naive({a*2,b*2,c,d});
		auto bns=cal(a,b,c,d);
		/* if(a==b){ */
		/* 	if(c==d){ */
		/* 		assert(!ans); */
		/* 	} */
		/* 	else{ */
		/* 		if(c<d && !ans || c>d && ans){ */
		/* 			err(a,b,c,d,ans); */
		/* 		} */
		/* 	} */
		/* } */
		/* else{ */
		/* 	if(a<b && !ans || a>b && ans){ */
		/* 		err(a,b,c,d,ans); */
		/* 	} */
		/* } */
		if(ans!=bns){
			err(a,b,c,d,ans);
		}
	}
}

void yamada::solve()
{
	inl(a,b,c,d);
	out(cal(a,b,c,d)?"Alice":"Bob");
}
