#include "../../template/multitest-template.hpp"
#include "../../tree/pruefer-code.hpp"
#include "../../tree/tree-query.hpp"
#include "../../graph/graph-template.hpp"
using namespace yamada;

bool check(UnweightedGraph &g,vc<bool> &fn){
	ll N=g.size();
	Tree tree(g);
	rep(u,N)rep(v,u+1,N){
		auto path=tree.path(u,v);
		if(path.size()%2)continue;
		ll st=0;
		bool reg=1;
		each(i,path){
			if(fn[i])++st;
			else --st;
			if(st<0)reg=0;
		}
		if(st)reg=0;
		if(reg)return 0;
	}
	return 1;
}

UnweightedGraph naive(ll N,vc<bool> &fn){
	vc<int> cur;
	auto dfs=[&](auto&& self)->UnweightedGraph{
		if(cur.size()==N-2){
			auto g=pruefer_code(cur);
			if(check(g,fn)){
				return g;
			}
			return{};
		}
		rep(i,N){
			cur.eb(i);
			auto g=self(self);
			if(!g.empty())return g;
			cur.pop_back();
		}
		return{};
	};
	return dfs(dfs);
}

void yamada::solve()
{
	/* inl(N); */
	/* auto toS=[&](ll msk)->string{ */
	/* 	string ans; */
	/* 	rep(i,N)ans+=(msk>>i&1? '#':'.'); */
	/* 	return ans; */
	/* }; */
	/* rep(msk,1<<N){ */
	/* 	vc<bool> fn(N); */
	/* 	rep(i,N)if(msk>>i&1)fn[i]=1; */
	/* 	auto g=naive(N,fn); */

	/* 	{ */
	/* 		bool ans=!g.empty(); */
	/* 		bool bns=!fn.front()|fn.back(); */
	/* 		assert(ans==bns); */
	/* 	} */
	/* 	if(!g.empty()){ */
	/* 		err(toS(msk)); */
	/* 		rep(u,N)err(u,g[u]); */
	/* 	} */
	/* } */

	inl(N);
	ins(S);
	if(!YesNo(S.front()==')' || S.back()=='('))return;
	if(S.front()==')'){
		rep(u,1,N)out(1,u+1);
	}
	else{
		rep(u,N-1)out(u+1,N);
	}
}
