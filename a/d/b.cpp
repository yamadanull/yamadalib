#include "../../template/template.hpp"
/* #include "../../segment-tree/segment-tree.hpp" */
/* #include "../../monoid/make-monoid.hpp" */
/* using namespace yamada; */
/* using T=pl; */
/* T F(T a,T b){return min(a,b);} */
/* T ti(){return {-infLL,-infLL};} */
/* using Mono=MyMonoid<T,F,ti>; */

void yamada::solve()
{
	inl(N,K);

	vl A(N),B(N); in(A,B);
	auto check=[&](ll x)->bool{
		auto C=A;
		V<T> init;
		rep(i,N)init[i]={A[i],Floor(A[i],B[i])};
		SegmentTree<Mono> seg(init);

		rep(t,K){
			auto[lim,i]=seg();
		}
	};
}
