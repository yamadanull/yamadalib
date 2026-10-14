#include "../../template/template.hpp"
#include "../../data-structure/union-find.hpp"
using namespace yamada;

void tc()
{
	inl(N);
	vl A(N),B(N); in(A,B);
	vl per(N); rep(i,N)per[i]=i;

	ll ans=-infLL;
	do{
		{
			UnionFind uf(N);
			rep(i,N)uf.unite(i,per[i]);
			if(uf.groups().size()>=2)continue;
		}
		vl C(N);
		rep(i,N)C[i]=A[per[i]];
		ll bns=0;
		rep(i,N){
			if(C[i]==B[i])++bns;
		}
		amax(ans,bns);
	}while(nxp(per));
	out(ans);
}
void yamada::solve() { ini(T); while(T--)tc(); }
