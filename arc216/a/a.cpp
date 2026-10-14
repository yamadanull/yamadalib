#include "../../template/template.hpp"
using namespace yamada;

ll type(string S){
	ll N=S.size();
	ll ans=0;
	for(ll l=0,r=0; l<N; l=r){
		while(r<N && S[l]==S[r])++r;
		if(S[l]==1 && (r-l)%2==0){
			if(l%2==0)--ans;
			else ++ans;
		}
	}
	return ans;
}

void tc()
{
	inl(N);
	ins(A,B);
	each(c,A)c-='0';
	each(c,B)c-='0';
	if(A[0]!=B[0])die(-1);
	if(A.back()!=B.back())die(-1);
	if(type(A)!=type(B))die(-1);

	// iをひっくり返す前。jはi-1の値
	constexpr ll LEN=5;
	vl dp(1<<LEN,infLL);
	dp[(ll)A[0]<<(LEN-1)]=0;
	rep(i,1,N){
		minpq<pl> q;
		rep(msk,1<<LEN)if(dp[msk]<infLL){
			q.emplace(dp[msk],msk);
		}
		while(!q.empty()){
			auto[d,msk]=q.top(); q.pop();
			if(dp[msk]!=d)continue;

			// jをひっくり返す
			rep(j,max(i-LEN,1LL),i){
				bool b0=(j==i-LEN? B[j-1]: msk>>(LEN-(i-j)-1)&1);
				bool b1=(j==i-1? A[j+1]: msk>>(LEN-(i-j)+1)&1);
				if(b0==b1){
					ll nsk=msk^(1<<(LEN-(i-j)));
					if(amin(dp[nsk],dp[msk]+1)){
						q.emplace(dp[nsk],nsk);
					}
				}
			}
		}

		vl ep(1<<LEN,infLL);
		rep(msk,1<<LEN){
			if(i>=LEN){
				if(B[i-LEN]==0 && msk&1)continue;
				if(B[i-LEN]==1 && !(msk&1))continue;
			}
			else{
				if(msk&1)continue;
			}
			ll nsk=msk/2+((ll)A[i]<<(LEN-1));
			amin(ep[nsk],dp[msk]);
		}
		dp=ep;
		/* out(dp); */
	}

	ll msk=0;
	rep(i,max(N-LEN,0LL),N)if(B[i]==1)msk|=1<<(LEN-(N-i));
	/* out(msk); */

	out(dp[msk]);
}
void yamada::solve() { ini(T); while(T--)tc(); }
