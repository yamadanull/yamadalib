#include "../../template/template.hpp"
#include "../../segment-tree/lamda-segment-tree.hpp"

void yamada::solve()
{
	inl(N);
	vc<int> A(N); in(A); each(a,A)--a;
	vl L(N);
	{
		vl st;
		rep(i,N){
			while(!st.empty() && A[st.back()]<A[i])st.pop_back();
			L[i]=(st.empty()? 0:st.back());
			st.eb(i);
		}
	}
	/* out("L:",L); */

	using T=pl;
	auto F=[&](T a,T b)->T{return min(a,b);};
	T ti{infLL,infLL};

	vl C(N); in(C);
	C=p_shf(A,C,1);
	vc<T> init(N);
	rep(i,N)init[i]={C[i],i};
	SegmentTree seg(init,F,ti);

	vl D(N); // 今の子の数
	ll ans=0;
	rep(u,1,N){
		ll p=seg.query(L[u],u).se;
		ans+=C[p]*(D[p]*2+1);
		D[p]++;
		seg.update(p,{C[p]*(D[p]*2+1),p});
	}
	out(ans);
}
