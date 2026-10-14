#include "../../template/template.hpp"
#include "../../data-structure/union-find.hpp"

void yamada::solve()
{
	inl(N);
	vl cur(N);
	rep(i,N)cur[i]=i;
	vvl As;
	do{
		As.eb(cur);
	}while(nxp(cur));

	V<bool> fn(As.size());

	sort(all(cur));
	auto dfs=[&](auto&& dfs,ll i)->void{
		if(i==N-1){
			ll fi=lb(As,cur);
			fn[fi]=1;
			return;
		}
		rep(j,i+1,N){
			swap(cur[i],cur[j]);
			dfs(dfs,i+1);
			swap(cur[i],cur[j]);
		}
	}; dfs(dfs,0);

	ll cnt=0;
	rep(i,As.size()){
		auto& A=As[i];
		UnionFind uf(N);
		rep(i,N)uf.unite(i,A[i]);

		if(fn[i]){
			out(A);
			/* rep(i,N)assert(A[i]!=i); */
			assert(uf.groups().size()==1);
			++cnt;
		}
		else{
			assert(uf.groups().size()>=2);
		}
	}
	out(cnt);
}
