#include "../../template/template.hpp"
#include "../../modulo/binomial.hpp"
#include "../../modint/montgomery-modint.hpp"
using namespace yamada;

using mint = LazyMontgomeryModInt<998244353>;
Binomial<mint> binom;
void tc()
{
	inl(N,K);
	vl A(N); in(A);
	map<ll,vl> mp;
	rep(i,N){
		ll key=A[i]%K;
		amin(key,K-key);
		mp[key].eb(i);
	}

	V<tuple<ll,ll,ll>> lrk;
	each2(key,pos,mp){
		ll n=pos.size();
		rep(pi,n)pos[pi]-=pi;

		for(ll l=0,r=0; l<n; l=r){
			while(r<n && pos[l]==pos[r])++r;
			lrk.eb(pos[l]+l,pos[l]+r,key);
		}
	}

	mint ans=1;
	each3(l,r,key0,lrk){
		ll key1=(K-key0)%K;
		if(key0==key1){
			vl B;
			rep(i,l,r)B.eb(A[i]);
			sort(all(B));
			vl C;
			for(ll l=0,r=0; l<B.size(); l=r){
				while(r<B.size() && B[l]==B[r])++r;
				C.eb(r-l);
			}
			ans*=binom(C);
		}
		else{
			ll cnt=0; // key0
			rep(i,l,r)if(A[i]%K==key0)++cnt;
			ans*=binom(r-l,cnt);
		}
	}
	out(ans);
}
void yamada::solve() { ini(T); while(T--)tc(); }
