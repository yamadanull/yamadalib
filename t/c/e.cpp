#include "../../template/template.hpp"
using namespace yamada;

void tc()
{
	inl(N);
	map<vl,bool> memo;
	auto dfs=[&](auto&& self,vl A)->bool{
		if(memo.count(A))return memo[A];
		vl B;
		auto efs=[&](auto&& telf)->bool{
			if(B.size()==N){
				if(Sum(B)==0)return 0;
				ll x=0;
				each(b,B)x^=b;
				if(x)return 0;
				auto nA=A;
				rep(i,N)nA[i]-=B[i];
				return !self(self,nA);
			}
			ll u=B.size();
			rep(i,A[u]+1){
				B.eb(i);
				if(telf(telf))return 1;
				B.pop_back();
			}
			return 0;
		};
		return memo[A]=efs(efs);
	};

	/* vl cur; */
	/* auto efs=[&](auto&& self)->void{ */
	/* 	if(cur.size()==N){ */
	/* 		dfs(dfs,cur); */
	/* 		return; */
	/* 	} */
	/* 	rep(i,N+1){ */
	/* 		cur.eb(i); */
	/* 		self(self); */
	/* 		cur.pop_back(); */
	/* 	} */
	/* }; efs(efs); */

	vl A(N); in(A);
	dfs(dfs,A);
	each2(A,b,memo)if(!b){
		out(A,":",b);
	}
}
void yamada::solve() { ini(T); while(T--)tc(); }
