#include "../../template/template.hpp"
#include "../../modint/montgomery-modint.hpp"

void yamada::solve()
{
	using mint = LazyMontgomeryModInt<998244353>;

	inl(N,M);
	// 勝ち負けの決まっている試合
	// 左が勝つ時true
	vvl dec(N);
	{
		rep(i,N)dec[i].resize(1<<i,-1);

		vl P(1<<N); in(P); each(p,P)--p;
		while(M--){
			inl(w,l); --w; --l;
			ll W=P[w];
			ll L=P[l];
			repr(i,N)if((W>>i&1)!=(L>>i&1)){
				ll round=N-i-1;
				if(L>>i&1){ // 左が勝つ
					if(dec[round][W>>(i+1)]==0)die(0);
					dec[round][W>>(i+1)]=1;
				}
				else{ // 右が勝つ
					if(dec[round][W>>(i+1)]==1)die(0);
					dec[round][W>>(i+1)]=0;
				}

				rep(r,round+1,N){
					// 第 S>>shif試合に選手Sはいる
					ll shif=N-r;

					if(W>>(shif-1)&1){ // 自分が右
						if(dec[r][W>>shif]==1)die(0);
						dec[r][W>>shif]=0;
					}
					else{ // 自分が左
						if(dec[r][W>>shif]==0)die(0);
						dec[r][W>>shif]=1;
					}

					if(L>>(shif-1)&1){ // 自分が右
						if(dec[r][L>>shif]==1)die(0);
						dec[r][L>>shif]=0;
					}
					else{ // 自分が左
						if(dec[r][L>>shif]==0)die(0);
						dec[r][L>>shif]=1;
					}
				}
				break;
			}
		}
	}

	ll cnt=0;
	rep(i,N)each(d,dec[i])if(d>=0)++cnt;
	out((mint(2)).pow((1<<N)-cnt));
}
