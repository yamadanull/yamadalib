#include "../../template/template.hpp"
using namespace yamada;

void tc()
{
	inl(N);
	vl A(N); in(A); each(a,A)--a;
	vl C(N); in(C);
	auto dp=C;

	vl ans;
	vp st;
	while(1){
		ans.eb(Min(dp));
		if(ans.size()==N)die(ans);
		vl ep(N,infLL);

		// [順列の値、最小値]
		// first: 添字単調減少、値単調増加、コストバラバラ、最小コスト単調減少
		st.clear();
		// 右側が最小値
		repr(i,N){
			while(!st.empty() && A[i]<st.back().fi)st.pop_back();
			if(!st.empty()){
				ll val=st.back().se+C[i];
				amin(ep[i],val);
				st.eb(A[i],min(dp[i],st.back().se));
			}
			else st.eb(A[i],dp[i]);
		}

		// 左側が最小値
		// [順列の値、そこをLとした区間の最小コスト]
		st.clear();
		ll nmin=infLL;
		repr(i,N){
			while(!st.empty() && A[i]<st.back().fi){
				amin(nmin,st.back().se);
				st.pop_back();
			}
			amin(ep[i],nmin+C[i]);
			amin(nmin,dp[i]);
			st.eb(A[i],nmin);
			nmin=infLL;
		}

		dp=ep;
	}
}
void yamada::solve() { ini(T); while(T--)tc(); }
