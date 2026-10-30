#include "../../template/multitest-template.hpp"
#include "../../segment-tree/lazy-segment-tree-utility.hpp"
using namespace yamada;

bool query(ll a){
	assert(1<=a && a<=N-1);
	fout("?",a);
	return STR()[0]=='Y';
}
void output(ll ans){ fout("!",ans); }

vl get_fn(ll N){
	sum_segtree<ll> fn(N);
	rep(i,1,(N+1)/2){
		fn.set(i,query(i));
	}

	ll cnt0=fn(1,(N+1)/2);
	ll cnt1=(N-1)/2-cnt0;
	if(cnt0<cnt1){
		rep(i,1,(N+1)/2)if(!fn[i]){
			ll j=N-i;
			bool b=query(j);
			if(!b){output(2); return{};}
		}
	}
	else{
		rep(i,1,(N+1)/2)if(fn[i]){
			ll j=N-i;
			bool b=query(j);
			if(b){output(2); return{};}
		}
	}
	rep(i,1,(N+1)/2)seg.set(N-i,1-seg[i]);
	if(N%2==0){
		if(!query(N/2)){output(2); return{};}
		fn.set(N/2,1);
	}
	return fn.get();
}

void yamada::solve()
{
	IN(N);
	auto fn=get_fn(N);
	if(fn.empty())return;
}
