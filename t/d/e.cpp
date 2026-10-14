#include "../../template/template.hpp"
using namespace yamada;

void tc()
{
	inl(N);
	set<pl> st;
	auto dfs=[&](auto&& self,vl A,vl B)->void{
		/* out("A:",A); */
		/* out("B:",B); */
		/* cout.flush(); */
		ll m=A.size();
		if(m==1){
			st.insert(mkp(A[0],B[0]));
			return;
		}
		rep(i,m-1){
			vl S;
			S.eb(A[i]);
			S.eb(A[i+1]);
			S.eb(B[i]);
			S.eb(B[i+1]);
			sort(all(S));

			vl C,D;
			rep(j,m){
				if(i==j)C.eb(S[1]);
				else if(j!=i+1)C.eb(A[j]);
			}
			rep(j,m){
				if(i==j)D.eb(S[2]);
				else if(j!=i+1)D.eb(B[j]);
			}
			self(self,C,D);
		}
	};

	vl A(N),B(N);
	in(A,B);
	dfs(dfs,A,B);
	each2(a,b,st){
		die(min(a,b));
	}
}
void yamada::solve() { ini(T); while(T--)tc(); }
