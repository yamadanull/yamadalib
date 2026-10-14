#include "../../template/template.hpp"
#include "../../data-structure/union-find.hpp"

void yamada::solve()
{
	inl(N,M,K);
	inl(A,B);
	vl C(K); in(C);

	vl W;
	{
		vc<array<ll,3>> uvw(M); in(uvw); each(u,v,w,uvw)--u,--v;
		sort(all(uvw),[](auto a,auto b){return a[2]<b[2];});

		UnionFind uf(N);
		each(u,v,w,uvw)if(uf.unite(u,v)){
			W.eb(min(w,A));
		}
	}
	W=mkrev(W);
	CumulativeSum cum(W);

	auto getC=[&](ll from,ll to)->ll{
		ll ans=A-to;
		ll bns=(from-to)*B;
		err(from,to,ans,bns);
		return min(ans,bns);
	};

	ll mid=bisect<ll>(-1,N,[&](ll i){return A<W[i]*B;});
	each(c,C){
		ll m=c/A;
		if(m>=N-1){out(0); continue;}
		amin(m,mid);
		err(m);

		ll ans=cum(m,N-1);
		if(m<mid){
			ll w=bisect<ll>(0,W[m],[&](ll w)->bool{ return getC(W[m],w)>c%A; });
			ans-=W[m]-w;
		}
		else{
			ll remc=c;
			remc-=mid*A;
			remc-=cum(mid,m)*B;
			assert(remc>=0);
			ans-=remc/B;
			amax(ans,0);
		}
		out(ans);
	}
}
