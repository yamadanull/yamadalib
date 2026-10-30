#include "../../template/multitest-template.hpp"
#include "../../fps/ntt-friendly-fps.hpp"
#include "../../modint/montgomery-modint.hpp"
#include "../../segment-tree/lazy-segment-tree-utility.hpp"
using namespace yamada;

bool query(ll a){
	fout("?",a);
	return STR()[0]=='Y';
}
void output(ll ans){ fout("!",ans); }

vl get_fn(ll N){
	sum_segtree<ll> seg(N);
	rep(i,1,(N+1)/2){
		seg.set(i,query(i));
	}

	ll cnt0=seg(1,(N+1)/2);
	ll cnt1=(N-1)/2-cnt0;
	/* err(cnt0,cnt1); */
	if(cnt0>cnt1){
		rep(i,1,(N+1)/2)if(!seg[i]){
			ll j=N-i;
			bool b=query(j);
			if(!b){output(2); return{};}
		}
	}
	else{
		rep(i,1,(N+1)/2)if(seg[i]){
			ll j=N-i;
			bool b=query(j);
			if(b){output(2); return{};}
		}
	}
	rep(i,1,(N+1)/2)seg.set(N-i,1-seg[i]);
	if(N%2==0){
		if(!query(N/2)){output(2); return{};}
		seg.set(N/2,1);
	}
	return seg.get();
}

template<typename mint>
bool check3(vl fn){
	using fps = FormalPowerSeries<mint>;
	ll N=len(fn);
	fps f(N);
	rep(i,N)if(fn[i])f[i]=1;
	auto g=f*f;
	rep(i,0,N,2)g[i]-=f[i/2];
	each(a,g)a/=2;
	rep(i,N)if(fn[i] && N-i*2>=0){
		mint cnt=g[N-i]-(f[N-i*2]-(i*3==N? 1:0));
		if(cnt!=0)return 1;
	}
	return 0;
}

using mint = LazyMontgomeryModInt<998244353>;
using nint = LazyMontgomeryModInt<167772161>;
void yamada::solve()
{
	IN(N);
	auto fn=get_fn(N);
	err(fn);
	if(fn.empty())return;
	output(check3<mint>(fn)||check3<nint>(fn)? 3:-1);
}
