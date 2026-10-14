#include "../../template/template.hpp"
/* #include "../../segment-tree/segment-tree.hpp" */
#include "../../tree/cartesian-tree.hpp"
/* #include "../../data-structure/sparse-table.hpp" */
/* #include "../../segment-tree/lazy-segment-tree-utility.hpp" */
#include "../../string/suffix-array.hpp"
using namespace yamada;
constexpr ll K=26;

vl getF(string S){
	ll N=S.size();
	string T="naist"; each(c,T)c-='a';
	ll M=T.size();

	vv(ll,npos,M,N,infLL);
	rep(i,N)rep(k,M)if(S[i]==T[k]){
		npos[k][i]=i;
	}
	rep(k,M)repr(i,N-1)if(npos[k][i]==infLL){
		npos[k][i]=npos[k][i+1];
	}

	vl ans(N,infLL);
	rep(i,N){
		ll L=i;
		rep(k,M){
			L=npos[k][L];
			if(L==infLL)break;
		}
		if(L<infLL)ans[i]=L-i+1;
	}
	return ans;
}

void yamada::solve()
{
	ins(S);
	each(c,S)c-='a';
	int N=S.size();
	auto F=getF(S);

	SuffixArray sa(S);
	auto lcp=LCPArray(sa).LCP;
	V<int> len(sa.size());
	rep(i,len.size()){
		len[i]=N-sa[i];
	}

	int M = lcp.size();
	ll ans=0;
	/* rep(i,1,lcp.size())if(lcp[i]==0)lcp[i]=inf; */
	auto[g,root]=CartesianTreeMin(lcp);
	auto ansadd=[&](int dep,int ndep,int u)->void{
		if(!inLR<ll>(0LL,sa[u],N))return;
		if(ndep==inf)ndep=N-sa[u];
		ll border=F[sa[u]];
		/* if(border<infLL)out(u,sa[u],":",dep,ndep,border); */
		if(border<=ndep){
			ll bns=ndep-max<ll>(dep,border-1);
			ans+=bns;
		}
	};

	auto dfs=[&](auto&& self,ll pval,ll u)->void{
		ll val=lcp[u];
		if(pval<val)ansadd(pval,val,u);
		each(v,g[u])self(self,val,v);
	}; dfs(dfs,0,root);

	rep(i,lcp.size())if(lcp[i]==0){
		ll ndep=N-sa[i];
		ll dep=i;
		out(sa[i],dep,ndep);
		if(dep<ndep)ansadd(dep,ndep,sa[i]);
	}
	out(sa.sa);

	/* // Suffix Array 内の番号 [L, R) 内のLCPがdep */
	/* auto dfs = [&](auto&& self, int L, int R, int dep)->void{ */
	/* 	if(L+1==R)return; */
	/* 	for (int l = L, r = L; l < R; l = r){ */
	/* 		r = seg.max_right([&](int mn){ return mn > dep; },l) + 1; */
	/* 		int ndep = (l + 1 == r? len[l] : seg.prod(l, r - 1).a); */
	/* 		if (ndep > dep){ */
	/* 			ansadd(dep,ndep,l); */
	/* 			self(self, l, r, ndep); */
	/* 		} */
	/* 	} */
	/* }; dfs(dfs, 0, M, 0); */
	out(ans);
}
