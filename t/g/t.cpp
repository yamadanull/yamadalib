#include "../../template/template.hpp"
#include "../../data-structure/union-find.hpp"
using namespace yamada;

void tc()
{
	inl(N);
	vp es;
	rep(i,N)rep(j,i+1,N)es.eb(i,j);

	vl mks;
	{
		vl A(es.size());
		rep(i,N-1)A[i]=1;
		reverse(all(A));
		do{
			ll mk=0;
			rep(i,A.size())if(A[i])mk+=1LL<<i;
			mks.eb(mk);
		}while(nxp(A));
	}
	out(mks.size());

	each(mk,mks){
		UnionFind uf(N);
		rep(i,es.size())if(mk>>i&1)uf.unite(es[i].fi,es[i].se);
		if(uf.size(0)!=N)continue;

		ll val=0;
		rep(i,es.size())if(mk>>i&1){
			auto[u,v]=es[i];
			val+=(u+1)*(v+1);
		}
		if(is_square(val)){
			out(val);
			rep(i,es.size())if(mk>>i&1){
				cout<<"out("<<es[i].fi+1<<","<<es[i].se+1<<");"<<"\n";
			}
			return;
		}
	}
}
void yamada::solve() { inl(T); while(T--)tc(); }
