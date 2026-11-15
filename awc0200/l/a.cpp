#include "../../template/template.hpp"
#include "../../tree/cartesian-tree.hpp"

void yamada::solve()
{
	IN(N,K,BIND(A,B)=~PR(LL,LL)[N]);
	auto C=mkrui(A);
	CartesianTree ct(B);
	ll ans=0;
	rep(u,N){
		auto[L,R]=ct.range[u];
		if(u-L<R-u){
			rep(l,L,u+1){// r:[rl,R]
				ll rl=lb(C,C[l]+K-B[u]);
				amax(rl,u+1);
				ans+=max(0LL,R+1-rl);
				err(u,l,rl,R);
			}
		}
		else{
			rep(r,u+1,R+1){
				ll lr=ub(C,C[r]-(K-B[u]));// l:[L,lr)
				amin(lr,u+1);
				ans+=max(0LL,lr-L);
				err(u,r,L,lr);
			}
		}
	}
	out(ans);
}
