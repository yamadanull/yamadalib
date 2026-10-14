#include "../../template/template.hpp"
#include "../../tree/pruefer-code.hpp"
#include "../../data-structure/union-find.hpp"
#include "../../graph/graph-template.hpp"
using namespace yamada;

bool check(UnweightedGraph g){
	ll N=Isqrt(g.size());
	rep(u,g.size())each(v,g[u]){
		ll i=u/N;
		ll j=u%N;
		ll I=v/N;
		ll J=v%N;
		if(abs(i-I)+abs(j-J)!=1)return 0;
	}

	vl tate(N),yoko(N);
	rep(i,N)rep(j,N)if(g[i*N+j].size()==1){
		yoko[i]++;
		tate[j]++;
	}
	if(Min(yoko)!=1)return 0;
	if(Min(tate)!=1)return 0;
	if(Max(yoko)!=1)return 0;
	if(Max(tate)!=1)return 0;
	return 1;
}

void yamada::solve()
{
	inl(N);
	vc<int> cur;
	/* auto dfs=[&](auto&& self)->UnweightedGraph{ */
	/* 	if(cur.size()==N*N-2){ */
	/* 		auto g=pruefer_code(cur); */
	/* 		if(check(g))return g; */
	/* 		return{}; */
	/* 	} */
	/* 	rep(x,N*N){ */
	/* 		cur.eb(x); */
	/* 		auto g=self(self); */
	/* 		if(!g.empty())return g; */
	/* 		cur.pop_back(); */
	/* 	} */
	/* 	return {}; */
	/* }; */
	vl di{-1,0,1,0};
	vl dj{0,-1,0,1};
	vc<tuple<ll,ll,ll,ll>> ijIJ;
	rep(i,N)rep(j,N-1)ijIJ.eb(i,j,i,j+1);
	rep(i,N-1)rep(j,N)ijIJ.eb(i,j,i+1,j);
	auto F=[&](auto P){
		vc<int> cur;
		auto dfs=[&](auto&& self)->void{
		};
		ll msk=MSK(N*N);
	};
	auto g=dfs(dfs);
	if(g.empty())die("NF");
	rep(u,N*N)err(u,g[u]);
}
