#include "../../template/template.hpp"
using namespace yamada;

constexpr int K=4;
ll divisibility(array<ll,K> a){
	ll ans=0;
	ll cof=1;
	rep(i,K)rep(j,i+1,K){
		if(a[j]%a[i]==0)ans|=cof;
		cof*=2;
	}
	return ans;
}

void yamada::solve()
{
	inl(N);
	map<ll,vc<array<ll,K>>> mp;
	rep(a,1,N)rep(b,a+1,N){
		ll d=b-a;
		array<ll,K> A{a,b,b+d,b+d+d};
		ll f=divisibility(A);
		mp[f].eb(A);
	}

	auto toS=[&](ll f)->vs{
		vs S(3);
		S[0]+=f>>0&1 ? '#':'.';
		S[1]+=f>>1&1 ? '#':'.';
		S[2]+=f>>2&1 ? '#':'.';
		S[0]+=f>>3&1 ? '#':'.';
		S[1]+=f>>4&1 ? '#':'.';
		S[0]+=f>>5&1 ? '#':'.';
		return S;
	};
	each2(f,a2,mp){
		if(popcnt(f)<=3)continue;
		out();
		each(s,toS(f))out(s);
		each(a1,a2)out(a1);
	}
}
