#include "../../template/template.hpp"

void yamada::solve()
{
	inl(H,W,N);
	map<ll,vl> Cs;
	rep(i,N){
		inl(a,b); --a; --b;
		Cs[a].eb(b);
	}

	ll ans=0;
	each2(r,cs,Cs){
		sort(all(cs));
		ans+=cs.back()*2;
	}

	vl costs;
	each2(r,cs,Cs){
		ll cost=infLL;
		amin(cost,cs.back());
		amin(cost,W-1-cs.front());
		rep(csi,cs.size()-1){
			ll d=cs[csi+1]-cs[csi];
			amin(cost,W-1-d);
		}
		costs.eb(cost*2);
	}
	sort(all(costs));
	ll sum=Sum(costs);
	ll n=costs.size();
	rep(i,2,n+1,2){
		rep(2){
			sum-=costs.back();
			costs.pop_back();
		}
		ll bns=(W-1)*i;
		bns+=sum;
		amin(ans,bns);
	}
	out(ans);
}
