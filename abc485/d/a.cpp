#include "../../template/template.hpp"

const int K=3;
void yamada::solve()
{
	IN(N,S=STR);
	each(c,S)c-='A';
	vl las(K,-infLL),fir(K,infLL);
	rep(i,N)amin(fir[S[i]],i),amax(las[S[i]],i);
	vl nx(K,N);
	ll ans=0;
	err(las);
	err(fir);
	repr(l,N){
		nx[S[l]]=l;
		err(nx);
		if(l>Max(fir)){
			ans+=max(0LL,Min(las)-Max(nx));
		}
	}
	out(ans);
}
