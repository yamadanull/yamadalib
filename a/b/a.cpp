#include "../../template/template.hpp"
using namespace yamada;

ll F(vint A){
	ll ans=0;
	each(i,a,A|Enumerate)ans|=i&a;
	return ans;
}

map<pl,vint> memo;
vint cal(ll N,ll K){
	if(memo.count(mkp(N,K)))return memo[mkp(N,K)];
	if(N==1){
		return memo[mkp(N,K)]={0};
	}
	ll T=msb(N-1);
	ll n=N-(1<<T);
	auto ans=cal(1<<T,K);
	auto bns=cal(n,K);
	each(b,bns)b|=1<<T;
	if(K>>T&1){
		each(b,bns)ans.eb(b);
		return memo[mkp(N,K)]=ans;
	}
	else{
		each(a,ans|Drop(n))bns.eb(a);
		each(a,ans|Take(n))bns.eb(a);
		return memo[mkp(N,K)]=bns;
	}
}

void yamada::solve()
{
	IN(N,K);
	if(!YesNo(msb(N-1)>=msb(K)))return;
	fout(mkiota(N));
	fout(cal(N,K));
	assert(F(cal(N,K))==K);
}
