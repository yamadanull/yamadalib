#include "../../template/multitest-template.hpp"
#include "../../tree/tree-query.hpp"
#include "../../graph/graph-template.hpp"
using namespace yamada;

bool check(Tree<UnweightedGraph>& tree,ll K,ll pos){
	ll N=tree.size(0);
	rep(u,K+1){
		ll v=K-u;
		if(!inLR(0,v,N)||!inLR(0,u,N))continue;
		if(u==v)continue;
		if(tree.len(u,v)==tree.len(u,pos)+tree.len(pos,v)){
			err(u,pos,v);
			return 1;
		}
	}
	return 0;
}

void yamada::solve()
{
	IN(N);
	auto g=graph(N);
	if(N%2==0)DIE(N+1);
	Tree tree(g);
	if(check(tree,N-1,(N-1)/2))DIE(N+1);
	if(check(tree,N,0))DIE(N+2);
	DIE(N);
}
