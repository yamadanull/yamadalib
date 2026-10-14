#include "../../template/template.hpp"

void yamada::solve()
{
	inl(N,K);
	const ll X=1e8;
	vl ans(K);

	ll M=K/N;
	if(M%2 && M>=3)--M;
	rep(d,M){
		ll L=N*d;
		ll R=N*(d+1);
		rep(i,L,R){
			if(d%2)ans[i]=(R-1-(i%N))*N+X;
			else ans[i]=i*N+X;
		}
	}

	if(M>=2){
		rep(I,M*N,K){
			ans[I]=K-I;
			ll i=I-M*N;
			ans[i]-=ans[I];
		}
	}
	if(M==1){
		rep(i,N-1)ans[i]=i+1;
		ans[N-1]=X;
		rep(i,N,K)ans[i]=X-(i%N+1);
	}

	vl bns(K);
	rep(i,K)bns[i]=i%N+1;

	{
		vl sum(N);
		rep(i,K)sum[bns[i]-1]+=ans[i];
		assert(Min(sum)==Max(sum));
		assert(Min(ans)>=1);
		assert(Max(ans)<=1e14);

		map<ll,bool> mp;
		each(a,ans){
			assert(!mp.count(a));
			mp[a]=true;
		}
	}

	out(ans);
	out("YES");
	out(bns);
}
