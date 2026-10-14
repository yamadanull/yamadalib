#include "../../template/template.hpp"
using namespace yamada;

map<vl,bool> memo;
bool naive(vl A){
	if(memo.count(A))return memo[A];
	/* err(A); */
	auto B=A;
	each(i,a,A|enumerate){
		rep(j,1,a+1){
			B[i]-=j;
			if(Any(B,[&](auto b)->bool{return b%2;})){
				if(!naive(B))return memo[A]=1;
			}
			B[i]+=j;
		}
	}
	return memo[A]=0;
}

ll count(vl A){
	ll nim=0;
	each(a,A)nim^=a;
	amin(nim,1);
	ll ans=0;
	each(a,A)if(a){
		ll mim=nim^a^(a-1);
		if(mim)++ans;
	}
	return ans;
}
bool cal(vl A){
	/* Sort(A); */
	/* ll N=A.size(); */
	/* vl B; */
	/* for(ll l=0,r=0; l<N; l=r){ */
	/* 	while(r<N && A[l]==A[r])++r; */
	/* 	if((r-l)%2){ */
	/* 		if(A[l])B.eb(A[l]); */
	/* 	} */
	/* } */
	/* if(len(B)==1){ */
	/* 	return !(B.front()==1); */
	/* } */
	/* if(len(B)==2){ */
	/* 	return !(B[0]%2==0 && B[1]==B[0]+1); */
	/* } */
	/* return 1; */
	ll nim=0;
	each(a,A)nim^=a;
	return nim!=1;
}

void exper(){
	inl(N,M);
	each(A,product(vl(N,M))){
		{
			bool fn=1;
			rep(i,N-1)if(A[i]>A[i+1])fn=0;
			if(!fn)continue;
		}
		if(All(A,[](auto a){return a%2==0;}))continue;
		auto ans=naive(A);
		auto bns=cal(A);
		if(ans!=bns)err(A,ans);
	}
}

void yamada::solve()
{
	inl(N);
	vl A(N); in(A);
	out(cal(A)?"Alice":"Bob");
}
