#include "../../template/multitest-template.hpp"
using namespace yamada;

using T=array<ll,3>;
void output2(ll H,ll W,vc<T> ans){
	vs S(H); rep(i,H)rep(j,W)S[i]+='.';
	rep(ci,ans.size()){
		auto[r,c,s]=ans[ci];
		for(auto i:{r,r+s})for(auto j:{c,c+s}){
			assert(S[i][j]=='.');
			S[i][j]=ci+'a';
		}
	}
	out();
	each(s,S)fout(s);
}
void output(ll H,ll W,vc<T> ans){
	out(ans.size());
	each3(r,c,s,ans)out(r+1,c+1,s);
}

void cal(vc<T> &ans,ll H,ll W,ll R,ll C){
	if(H%2==0 || W%2==0 || H==3 || W==3){
		amin(H,H/2*2);
		amin(W,W/2*2);
		rep(i,R,R+H,2)rep(j,C,C+W,2)ans.eb(T{i,j,1});
		return;
	}
	if(H%4==1 && H==W){
		ll N=H;
		cal(ans,2,N-3,R,C+1);
		cal(ans,2,N-3,R+N-2,C+2);
		cal(ans,N-3,2,R+2,C);
		cal(ans,N-3,2,R+1,C+W-2);
		if(H>=9)cal(ans,H-4,W-4,R+2,C+2);
		ans.eb(T{R,C,N-1});
		return;
	}

	ll h=(H%4==1? H:H-2);
	ll w=(W%4==1? W:W-2);
	ll n=min(h,w);
	cal(ans,n,n,R,C);
	if(H>n && W>n)cal(ans,H-n,W-n,R+n,C+n);
	if(H>n)cal(ans,H-n,n,R+n,0);
	if(W>n)cal(ans,n,W-n,0,C+n);
}

vc<T> cal(ll H,ll W){
	vc<T> ans;
	cal(ans,H,W,0,0);
	return ans;
}

void yamada::solve()
{
	inl(H,W);
	output(H,W,cal(H,W));
}
