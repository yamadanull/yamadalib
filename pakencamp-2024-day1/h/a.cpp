#include "../../template/template.hpp"
#include "../../modint/arbitrary-modint.hpp"
#include "../../modint/montgomery-modint.hpp"

using mint = LazyMontgomeryModInt<998244353>;
using nint=ArbitraryModInt;
void yamada::solve()
{
	ins(S); reverse(all(S)); each(c,S)c-='0';
	if(S.size()==1 && S[0]==1)die(1);
	nint::set_mod(mint::get_mod()-1);
	string T=S;
	rep(i,T.size())if(T[i]>char(0)){
		--T[i];
		rep(j,i)T[j]=char(9);
		break;
	}

	string U=S; U+=char(0);
	rep(i,U.size())if(U[i]<char(9)){
		++U[i];
		rep(j,i)U[j]=char(0);
		break;
	}
	/* each(c,S)c+='0'; */
	/* each(c,T)c+='0'; */
	/* each(c,U)c+='0'; */
	/* reverse(all(S)); */
	/* reverse(all(T)); */
	/* reverse(all(U)); */
	/* out(S,T,U); */
	/* return; */

	nint t=0;
	rep(i,T.size()){
		t+=((nint)10).pow(i)*T[i];
	}

	mint kiyo=((mint)2).pow(t.get())/2;
	mint ans=0;
	rep(i,U.size()){
		ans+=kiyo*((mint)10).pow(i)*U[i];
	}
	out(ans);
}
