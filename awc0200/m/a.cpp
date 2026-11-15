#include "../../template/template.hpp"
#include "../../modint/montgomery-modint.hpp"

using mint = LazyMontgomeryModInt<1'000'000'007>;
const int BS = 10;
void yamada::solve()
{
	IN(S=STR,D);
	each(c,S)c-='0';
	ll N=len(S);

	VVV(mint,ep,N+1,BS,2); // S[0,i) 以下で、最後の桁がj、Nへの針付き
	ep[0][0][1]=1;
	rep(i,N)rep(x,BS)rep(p,2){
		rep(X,BS){
			if(p&&X>S[i])continue;
			ll P=p&&X==S[i];
			ep[i+1][X][P]+=ep[i][x][p];
		}
	}
	// 0を除外
	ep[0][0][1]=0;
	rep(i,1,N+1)ep[i][0][0]-=1;

	VVVV(mint,dp,N+1,BS,2,2); // S[0,i) のときの、部分列の右端がiのときの答え
	// そこから部分列をスタートするもの
	rep(i,N+1)rep(x,BS)rep(p,2){
		ll q=x>0;
		dp[i][x][p][q]=ep[i][x][p];
	}
	// 既に部分列が始まっているもの
	rep(i,N)rep(x,BS)rep(p,2)rep(q,2){ // p:Nへの貼り付き q:非ゼロが現れているか
		rep(X,BS){ // x->X
			if(q&&abs(x-X)>D)continue;
			if(p&&X>S[i])continue;
			ll P=p&&X==S[i];
			ll Q=q||X>0;
			dp[i+1][X][P][Q]+=dp[i][x][p][q];
		}
	}

	mint ans=0;
	rep(i,N+1)rep(x,BS)rep(q,2){
		ll p=0;
		ans+=dp[i][x][p][q]*((mint)BS).pow(N-i);
	}
	mint curn=1;
	repr(i,N+1){
		if(i<N)curn+=((mint)BS).pow(N-i-1)*S[i];
		rep(x,BS)rep(q,2){
			ll p=1;
			ans+=dp[i][x][p][q]*curn;
		}
	}
	out(ans);
}
