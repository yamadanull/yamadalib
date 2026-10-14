#include "../../template/multitest-template.hpp"
using namespace yamada;

using T=array<ll,3>;
void output(vc<T> ans){
	out(ans.size());
	each3(r,c,s,ans)out(r+1,c+1,s);
}
vc<T> make55(){
	ll N=9;
	vc<T> cur;
	vc<T> ans;
	auto dfs=[&](auto&& self,ll R,ll C,VV<bool> A)->bool{
		if(R==N-1 && C==N-1){
			if(cur.size()==N*(N-1)/4 && A==Rotate(A)){
				vs S(N); rep(i,N)rep(j,N)S[i]+='.';
				rep(ci,cur.size()){
					auto[r,c,s]=cur[ci];
					for(auto i:{r,r+s})for(auto j:{c,c+s}){
						S[i][j]=ci+'a';
					}
				}
				out();
				each(s,S)fout(s);
			}
			return 0;
		}
		ll nR=R+(C+1)/N;
		ll nC=(C+1)%N;
		if(R!=nR){
			ll cnt=0;
			rep(j,N)cnt+=A[R][j];
			if(cnt!=N-1)return 0;
		}
		if(self(self,nR,nC,A))return 0;
		if(A[R][C])return 0;
		rep(s,1,N){
			ll r=R+s;
			ll c=C+s;
			if(r>=N)break;
			if(c>=N)break;
			/* if(R==C)continue; */
			/* if(R==c)continue; */
			/* if(r==C)continue; */
			/* if(r==c)continue; */
			if(A[r][C])continue;
			if(A[R][c])continue;
			if(A[r][c])continue;
			auto B=A;
			B[R][C]=1;
			B[r][C]=1;
			B[R][c]=1;
			B[r][c]=1;
			cur.eb(T{R,C,s});
			if(self(self,nR,nC,B))return 0;
			cur.pop_back();
		}
		return 0;
	};
	vv(bool,A,N,N,0);
	YesNo(dfs(dfs,0,0,A));
	return ans;
}
vc<T> cal_11(ll N){
	assert(N%4==1);
	auto base=make55();
	vc<T> ans;
	rep(t,0,N-1,4){
		rep(i,4)rep(j,4){
			ll I=i+t*4;
			ll J=j+t*4;
		}
	}
	return ans;
}

vc<T> cal_odd(ll H,ll W){
	ll h=(H%4==1? H:H-2);
	ll w=(W%4==1? W:W-2);
	ll n=min(h,w);
	auto ans=cal_11(n);
	rep(i,n,H,2)rep(j,1,W,2)ans.eb(T{i,j,1});
	rep(i,1,H-2,2)rep(j,n,W,2)ans.eb(T{i,j,1});
	return ans;
}

vc<T> cal_eve(ll H,ll W){
	amin(H,H/2*2);
	amin(W,W/2*2);
	vc<T> ans;
	rep(i,0,H,2)rep(j,0,W,2)ans.eb(T{i,j,1});
	return ans;
}

void yamada::solve()
{
	/* inl(H,W); */
	make55();
	/* if(H%2==0 || W%2==0 || H==3 || W==3){ */
	/* 	output(cal_eve(H,W)); */
	/* 	return; */
	/* } */
	/* output(make55()); */
}
