#include "../../template/template.hpp"
using namespace yamada;

void tc()
{
	const ll log=60;
	inl(N,W);
	vvl Y(log+1);
	rep(i,N){
		inl(x,y);
		Y[x].eb(y);
	}

	ll ans=0;
	rep(i,log)if(!Y[i].empty()){
		sort(all(Y[i])); reverse(all(Y[i]));
		if(W>>i&1){
			ans+=Y[i][0];
			rep(j,1,Y[i].size(),2){
				Y[i+1].eb(Y[i][j]+(j==Y[i].size()-1? 0:Y[i][j+1]));
			}
		}
		else{
			rep(j,0,Y[i].size(),2){
				Y[i+1].eb(Y[i][j]+(j==Y[i].size()-1? 0:Y[i][j+1]));
			}
		}
	}
	out(ans);
}

void yamada::solve() { inl(TC); while(TC--)tc(); }
