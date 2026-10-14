#include "../../template/template.hpp"
using namespace yamada;

void tc()
{
	inl(N);
	vl A(N); in(A);
	sort(all(A));
	// a==A[L]
	auto dfs=[&](auto&& dfs,ll L,ll a)->bool{
		ll M=ub(A,A[L]);
		if(M==N){
			if(a==0)return 1;
			if(a==1)return 0;
			return 1;
		}

		// step2
		if(a==0){
			bool nx=dfs(dfs,M,A[M]-A[L]);
			if(nx){ // 0をなくした状態でわたしてはいけない
				if(M-L==1)return 0;
				return 1;
			}
			// 0をなくした状態でわたせばよい
			return 1;
		}

		// step1
		bool nx=dfs(dfs,L,0);
		if(nx){ // 0にした状態で渡してはいけない
			if(a==1)return 0;
			return 1;
		}
		// 0にして渡せばよい
		return 1;
	};

	bool ans=dfs(dfs,0,A[0]);
	out(ans? "Alice":"Bob");
}
void yamada::solve() { ini(T); while(T--)tc(); }
