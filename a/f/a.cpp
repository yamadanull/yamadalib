#include "../../template/multitest-template.hpp"
#include "../../enumerate/sequences.hpp"
#include "../../data-structure/union-find.hpp"
using namespace yamada;

bool cal(){
	auto[K,A]=[]()->pair<ll,vint>{
		IN(N,K,P=--INT*N);
		UnionFind uf(N);
		rep(i,N){
			uf.unite(i,P[i]);
		}
		auto grs=uf.groups();
		vint ans;
		each(gr,grs)ans.eb(len(gr));
		return{K,ans};
	}();

	Sort(A);
	err(K,A);
	each(a,A)if(a>=K+2)return 0;
	if(Contains(A,K+1)){
		A.pop_back(); // Bobに押し付けるK+1
		ll cnt1=0;
		ll delsum=0;
		each(a,A){
			if(a==1)++cnt1;
			else delsum+=a;
		}
		if(K==1)return cnt1%2;
		// K>=2 -> 残すものが 1が(K+1)の倍数個、K+1が1個でなければならない
		delsum+=modulo(cnt1,K+1);
		return 1<=delsum && delsum<=K;
	}

	bool ans=0;
	rep(K2,1,K+1)SumFixedSequences<true>(K2,[&](auto B){
		if(ans)return;
		vint remA;
		each(a,A|Rev){
			if(B.empty())remA.eb(a);
			else if(a>B.back())remA.eb(a);
			else if(a==B.back())B.pop_back();
			else return;
		}
		if(!B.empty())return;

		ll n=len(remA);
		ll nxsm=Sum(remA|Take(Min(n,K))|Ofs(-1));
		if(nxsm<=K){
			ans=1;
		}
	});
	return ans;
}

void yamada::solve()
{
	out(cal()?"Alice":"Bob");
}
