#include "../../template/template.hpp"
#include "../../orderedmap/orderedset.hpp"
#include "../../misc/compress.hpp"
#include "../../segment-tree/lazy-segment-tree-utility.hpp"

void yamada::solve()
{
	ll M=26;
	inl(N,Q);
	V<pair<string,ll>>base;
	rep(i,N){
		ins(S);
		base.eb(S,i);
	}
	sort(all(base));

	Set<pair<string,ll>,false>st(base);

	while(Q--){
		inl(x); --x;
		ins(T);
		auto[S,i]=st.kth_element(x)->key;
		st.erase(mkp(S,i));
		pair<string,ll>Ti=mkp(T,i);
		st.insert(Ti);
		/* out(S,T,i); */
	}

	vs ans(N);
	rep(i,N){
		auto[S,j]=st.kth_element(i)->key;
		ans[j]=S;
	}
	out(ans);
}
