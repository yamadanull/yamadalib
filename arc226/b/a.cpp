#include "../../template/multitest-template.hpp"

constexpr int LG=61;
void yamada::solve()
{
	inl(N,M);
	vl A(LG);
	rep(t,M)in(A[t]);
	auto check=[&](ll X)->bool{
		auto B=A;
		ll cur=LG-1;
		auto cur_upd=[&](){
			while(cur>=0 && B[cur]==0)--cur;
		};
		cur_upd();

		repr(t,LG)if(X>>t&1){
			i128 rem=N;
			ll nd=0;
			while(rem && cur>=0){
				/* fout("rem,cur:",rem,cur); */
				/* assert(rem>=0); */
				{
					ll d=t-cur;
					if(d<0)return 1;
					rep(d-nd)rem*=2;
					nd=d;
				}

				ll red=min<i128>(rem,B[cur]);
				B[cur]-=red;
				rem-=red;

				cur_upd();
			}
		}
		return Max(B)>0;
	};

	ll ans=bisect<ll>(-1,MSK(LG),check);
	out(ans);
}
