#include "../../template/multitest-template.hpp"
#include "../../dp/inversion-counting.hpp"
#include "../../shortest-path/bfs.hpp"
#include "../../graph/graph-template.hpp"
using namespace yamada;

VV<int> mkP(int N,int K){
	VV<int> PS;
	nxp(N,[&](auto P){PS.eb(P);});
	int M=PS.size();
	UnweightedGraph g(M);
	rep(u,M){
		auto p=PS[u];
		rep(l,N-K*2+1){
			auto q=p;
			rep(i,l,l+K)swap(q[i],q[i+K]);
			int v=lb(PS,q);
			g[u].eb(v);
		}
	}
	auto dp=bfs(g);
	VV<int> ans;
	rep(u,M)if(dp[u]>=0){
		ans.eb(PS[u]);
	}
	return ans;
}
void expmt(ll N,ll K){
	auto PS=mkP(N,K);
	/* VV<int> QS; */
	nxp(N,[&](auto P){
		rep(i,N)if(i%K!=P[i]%K)return;
		err(P);
		/* ll invsum=0; */
		vl inv(K);
		rep(k,K){
			vc<int>A;
			rep(i,k,N,K)A.eb(P[i]);
			inv[k]=inversion_counting(A)%2;
		}

		bool ans=Max(inv)==Min(inv);
		bool bns=binary_search(all(PS),P);
		/* err(inv,bns); */
		err(ans,bns);
		assert(!ans^bns);
	});
}
vc<int> naive(vc<int> A,int K){
	ll N=A.size();
	auto ans=A;
	each(p,mkP(N,K)){
		amin(ans,p_shf(p,A));
	}
	return ans;
}

vc<int> cal(vc<int> A,int K){
	int N=A.size();
	/* if(N%K==0){ */
	/* 	vv(int,B,N/K,K); */
	/* 	rep(i,N)B[i/K][i%K]=A[i]; */
	/* 	sort(all(B)); */
	/* 	vc<int> ans(N); */
	/* 	rep(i,N)ans[i]=B[i/K][i%K]; */
	/* 	return ans; */
	/* } */
	rep(k,K){
		vc<int> B;
		rep(i,k,N,K)B.eb(A[i]);
		sort(all(B));
		rep(i,k,N,K)A[i]=B[i/K];
	}
	return A;
}

void yamada::solve()
{
	inl(N,K);
	expmt(N,K);
	/* nxp(N,[&](auto A){ */
	/* 	auto c=cal(A,K); */
	/* 	auto n=naive(A,K); */
	/* 	if(c!=n){ */
	/* 		err(A,c,n); */
	/* 		/1* err(c); *1/ */
	/* 		/1* err(n); *1/ */
	/* 	} */
	/* }); */
}
