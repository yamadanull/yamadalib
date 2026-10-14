#include "../../template/template.hpp"

void yamada::solve()
{
	inl(N);
	ins(S);
	vl A(N); in(A);

	vp lr;
	for(ll l=0,r=0; l<N; l=r){
		while(r<N && S[l]==S[r])++r;
		if(l>0 || S[l]=='.')lr.eb(l,r);
	}
	if(lr.size()%2==0)lr.pop_back();

	ll K=lr.size();
	vl val(K,-infLL),cnt(K);
	rep(k,K){
		auto[l,r]=lr[k];
		rep(i,l,r)amax(val[k],A[i]);
		rep(i,l,r)if(A[i]==val[k])++cnt[k];
	}

	ll MX=0;
	each(v,val)amax(MX,v);
	// 木のない良い区間、木のある良い区間
	vl st0,st1;
	rep(k,K){
		if(val[k]==MX)(k%2? st1:st0).eb(k);
	}

	set<ll> trees;
	each(k,st0){
		if(k>=2)trees.insert(k-1);
		if(k+2<K)trees.insert(k+1);
	}
	each(k,st1){
		trees.insert(k);
	}

	ll ans=0;
	each(k,trees){
		ans+=cnt[k-1]*cnt[k+1];
	}

	out(ans);
}
