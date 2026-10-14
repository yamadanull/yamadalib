#include "../../template/template.hpp"

constexpr int N=5;
constexpr int lim[N]={1,9,81,729,6561};
void yamada::solve()
{
	array<queue<ll>,5> q;
	auto emp=[&](ll i)->bool{return q[i].empty();};
	auto get=[&](ll i)->ll{ return emp(i)? infLL: q[i].front(); };
	auto top=[&](ll i)->ll{ return emp(i)? infLL: q[i].back(); };
	auto MN=[&](ll n)->ll{
		ll ans=infLL;
		rep(i,n)amin(ans,get(i));
		return ans;
	};
	auto mni=[&](ll n)->ll{
		ll a=MN(n);
		rep(i,n)if(a==get(i))return i;
		return -1;
	};

	auto que1=[&](ll x){
		q[0].push(x);

		ll n=-1;
		for(ll nsiz=0,i=0; i<N; i++){
			nsiz+=q[i].size();
			if(lim[i]>nsiz){ n=i; break; }
		}

		vp ans;
		auto mov=[&](ll i,ll j){
			q[j].push(q[i].front());
			q[i].pop();
			ans.eb(i,j);
		};

		ll siz=q[n].size();
		rep(siz){
			while(MN(n)<get(n))mov(mni(n),n);
			mov(n,n);
		}
		while(MN(n)<infLL)mov(mni(n),n);

		fout(ans.size());
		each2(i,j,ans)fout(i+1,j+1);
	};

	auto que2=[&](){
		ll i=mni(N);
		fout(i+1);
		q[i].pop();
	};

	inl(Q);
	Q*=2;
	while(Q--){
		inl(op);
		if(op==1){
			inl(x);
			que1(x);
		}
		else que2();
	}
}
