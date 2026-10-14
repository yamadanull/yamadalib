#include "../../template/template.hpp"
#include "../../data-structure/union-find.hpp"
using namespace yamada;

void tc()
{
	inl(N);
	vl A(N),B(N); in(A,B);
	each(a,A)--a;
	each(b,B)--b;
	vvl posa(N),posb(N);
	rep(i,N)posa[A[i]].eb(i),posb[B[i]].eb(i);

	UnionFind uf(N);
	ll ans=N;
	ll FN=-1; // 損なサイクルがあるか
	V<bool> fn(N);
	rep(a,N){
		ll n=posa[a].size();
		ll m=posb[a].size();
		ans-=max(n-m,0LL);
		if(n-m>0)FN=posa[a][0];
		if(n-m!=0)fn[a]=1;
		vl pos;
		each(i,posa[a])pos.eb(i);
		each(i,posb[a])pos.eb(i);
		pos=mkuni(pos);
		rep(pi,pos.size()-1)uf.unite(pos[pi],pos[pi+1]);
	}

	rep(a,N)if(fn[a]){
		each(i,posa[a])uf.unite(FN,i);
	}

	if(uf.groups().size()>=2){
		if(FN<0)ans-=uf.groups().size();
		else ans-=uf.groups().size()-1;
	}

	/* { */
	/* 	auto C=A,D=B; */
	/* 	sort(all(C)); */
	/* 	sort(all(D)); */
	/* 	if(C==B && uf.groups().size()==1)ans=N; */
	/* } */
	out(ans);
}
void yamada::solve() { ini(T); while(T--)tc(); }
