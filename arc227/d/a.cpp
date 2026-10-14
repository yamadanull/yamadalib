#include "../../template/template.hpp"
#include "../../misc/all.hpp"
using namespace yamada;

constexpr int MAX=500;
constexpr int DIV=20;
constexpr int CNT=(MAX+DIV-1)/DIV;
int S[MAX][CNT];
ll H[CNT][1<<DIV];
ll SSSsiz;
ll SSS[MAX*(MAX-1)*(MAX-2)/6+MAX];

ll genh(string s){
	ll ans=0;
	ll M=s.size();
	rep(j0,0,M,DIV){
		ll a=0;
		rep(j,j0,min(j0+DIV,M))if(s[j]=='1')a|=1LL<<(j-j0);
		ans+=H[j0/DIV][a];
	}
	return ans;
}

void yamada::solve()
{
	rep(bi,CNT){
		ll H2[DIV];
		each(h,H2)h=randint(0,1LL<<52);
		rep(msk,1,1<<DIV){
			ll t=lsb(msk);
			int nsk=msk^1<<t;
			H[bi][msk]=H[bi][nsk]+H2[t];
		}
	}

	ini(N,M,Q);
	rep(i,N){
		ins(s);
		SSS[SSSsiz++]=genh(s);
		rep(j,M)if(s[j]=='1'){
			int bi=j/DIV;
			int bj=j-bi*DIV;
			S[i][bi]|=1<<bj;
		}
	}

	rep(i,N)rep(j,i+1,N){
		ll h=0;
		rep(bi,CNT)h+=H[bi][S[i][bi]&S[j][bi]];
		rep(k,j+1,N){
			ll h2=h;
			rep(bi,CNT){
				h2+=H[bi][S[k][bi]&(S[i][bi]^S[j][bi])];
			}
			SSS[SSSsiz++]=h2;
		}
	}

	sort(SSS,SSS+SSSsiz);
	while(Q--){
		ins(t);
		ll h=genh(t);
		ll SSSi=lower_bound(SSS,SSS+SSSsiz,h)-SSS;
		YesNo(SSSi<SSSsiz && SSS[SSSi]==h);
	}
}
