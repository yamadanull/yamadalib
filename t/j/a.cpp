#include "../../template/template.hpp"
#include "../../modint/montgomery-modint.hpp"
using namespace yamada;

// return 値以上にはBを使ったほうがいい
ll cal_border(ll A,ll B){
	assert(A>=1 && B>=2);
	auto check=[&](ll x)->bool{
		ll gainA=A;
		ll gainB=x*(B-1);
		return gainA>gainB;
	};
	return bisect<ll>(-1,1<<30,check);
}

// return 値回目からはBを使ったほうがいい
ll cal_acnt(ll A,ll B){
	ll border=cal_border(A,B);
	return ceil(border,A);
}

using mint = LazyMontgomeryModInt<998244353>;
mint cal_res(ll A,ll B,ll acnt,ll bcnt){
	mint ans=A*acnt;
	ans*=((mint)B).pow(bcnt);
	return ans;
}

void tc()
{
	inl(A,B,K);
	if(A>=1 && B>=2){
		ll acnt=min(K,cal_acnt(A,B));
		ll bcnt=K-acnt;
		die(cal_res(A,B,acnt,bcnt));
	}

	if(abs(A)>=1 && B<=-2){
		bool a_is_neg=(A<0);
		A=abs(A);
		B=abs(B);

		ll acnt=min(K,cal_acnt(A,B));
		ll bcnt=K-acnt;
		if(bcnt%2==a_is_neg)die(cal_res(A,B,acnt,bcnt));
		if(acnt==K)die(cal_res(A,B,acnt-1,bcnt+1));
		if(acnt==0)die(cal_res(A,B,acnt+1,bcnt-1));
		--acnt; --bcnt;
		i128 na=A*acnt;
		i128 ans=na+A+A;
		i128 bns=na*B*B;
		if(ans<bns)die(cal_res(A,B,acnt,bcnt+2));
		else die(cal_res(A,B,acnt+2,bcnt));
	}

	if(A>=1)die((mint)A*K);
	if(B==-1 && A<=-1)die((mint)A*(1-K));
	out(0);
}
void yamada::solve() { inl(T); while(T--)tc(); }
