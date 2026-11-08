#include "../../template/multitest-template.hpp"
#include "../../modint/montgomery-modint.hpp"

using mint = LazyMontgomeryModInt<998244353>;
void yamada::solve()
{
	IN(M);
	ll N=M*3+10;
	vl A(N);
	rep(M)A[LL()]=1;

	VVV(mint,dp,N+1,2,2);
	repr(i,N-2)if(A[i]){ // iを左端として選ぶ
		// ふたつめ
		rep(p,2)if(!p||A[i+1])rep(q,2)if(!q||A[i+2])if(p+q==1){
			dp[i][p][q]+=1;
		}
		// みっつめ
		rep(p,2)rep(q,2){
			if(!p&&!q)continue;
			if(p){
				ll I=i+1;
				ll P=q;
				ll Q=1-q;
				dp[i][p][q]+=dp[I][P][Q];
			}
			else{
				ll I=i+2;
				ll P=1;
				rep(Q,2){
					dp[i][p][q]+=dp[I][P][Q];
				}
			}
		}
	}
	rep(i,N-2)if(A[i]){
		rep(p,2)if(!p||A[i+1])rep(q,2)if(!q||A[i+2])if(p+q==1)dp[i][p][q]-=1;
	}

	mint ans=(M+1)*M/2;
	each(d,dp|Join|Join)ans+=d;
	out(ans);
}
