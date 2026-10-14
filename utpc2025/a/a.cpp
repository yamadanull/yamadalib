#include "../../template/template.hpp"
#include "../../string/z-algorithm.hpp"
using namespace yamada;

vl dal(vl A,vl B,vl C){
	{
		auto AB=A,BA=B;
		each(a,A)BA.eb(a);
		each(b,B)AB.eb(b);
		if(AB>BA)swap(A,B);
	}
	ll N=A.size();
	ll M=B.size();
	ll K=C.size();

	vl cnt(K),dnt(K);
	each(c,C)++cnt[c];
	each(a,A)++dnt[a];
	each(b,B)++dnt[b];
	rep(i,K)if(dnt[i]>cnt[i])return vl(K,infLL);

	ll DIV=A[0],EIV=B[0];
	rep(i,N)if(A[i]!=DIV){
		if(A[i]>DIV)DIV++;
		break;
	}
	rep(j,M)if(B[j]!=EIV){
		if(B[j]>EIV)EIV++;
		break;
	}

	vl ans;
	rep(i,DIV)rep(cnt[i]-dnt[i])ans.eb(i);
	each(a,A)ans.eb(a);
	rep(i,DIV,EIV)rep(cnt[i]-dnt[i])ans.eb(i);
	each(b,B)ans.eb(b);
	rep(i,EIV,K)rep(cnt[i]-dnt[i])ans.eb(i);
	return ans;
}

vl cal(vl A,vl B,vl C){
	ll N=A.size();
	ll M=B.size();
	ll K=C.size();
	vl BA;
	each(b,B)BA.eb(b);
	each(a,A)BA.eb(a);
	auto za=z_algorithm(BA);

	auto D=A;
	{
		bool FN=0;
		rep(i,N){
			ll len=min(M,N-i);
			if(za[i+M]>=len){
				rep(j,len,M)D.eb(B[j]);
				FN=1;
				break;
			}
		}
		if(!FN)return vl(K,infLL);
	}
	ll L=D.size();
	ll DIV=D[0];

	vl cnt(K);
	each(c,C)++cnt[c];
	vl dnt(K);
	each(d,D)++dnt[d];
	rep(i,K)if(cnt[i]<dnt[i])return vl(K,infLL);

	rep(i,L)if(D[i]!=DIV){
		if(D[i]>DIV)DIV++;
		break;
	}

	vl ans;
	rep(i,DIV)rep(cnt[i]-dnt[i])ans.eb(i);
	each(d,D)ans.eb(d);
	rep(i,DIV,K)rep(cnt[i]-dnt[i])ans.eb(i);
	return ans;
}

void tc()
{
	inl(N,M,K);
	vl A(N),B(M),C(K); in(A,B,C);
	each(a,A)--a;
	each(b,B)--b;
	each(c,C)--c;

	auto ans=cal(A,B,C);
	amin(ans,cal(B,A,C));
	amin(ans,dal(A,B,C));

	if(ans[0]==infLL)out(-1);
	else{
		each(a,ans)++a;
		out(ans);
	}
}
void yamada::solve() { ini(T); while(T--)tc(); }
