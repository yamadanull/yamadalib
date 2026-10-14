#include "../../template/template.hpp"
#include "../../data-structure/union-find.hpp"

void yamada::solve()
{
	inl(H,W);
	auto idx=[&](ll i,ll j){return i*W+j;};
	vv(ll,A,H,W); in(A);
	vl di{-1,0,1,0};
	vl dj{0,-1,0,1};
	UnionFind uf(H*W);
	rep(i,H)rep(j,W){
		rep(x,4){
			ll I=i+di[x];
			ll J=j+dj[x];
			if(!inLR(0LL,I,H))continue;
			if(!inLR(0LL,J,W))continue;
			if(A[i][j]==A[I][J])uf.unite(idx(i,j),idx(I,J));
		}
	}

	auto grs=uf.groups();
	vl belong(H*W);
	rep(ci,grs.size())each(gri,grs[ci])belong[gri]=ci;

	map<pl,set<ll>> mp;
	rep(i,H)rep(j,W){
		rep(x,4){
			ll I=i+di[x];
			ll J=j+dj[x];
			if(!inLR(0LL,I,H))continue;
			if(!inLR(0LL,J,W))continue;
			if(A[i][j]!=A[I][J]){
				ll ci=belong[idx(i,j)];
				ll C=A[I][J];
				ll CI=belong[idx(I,J)];
				mp[mkp(ci,C)].insert(CI);
			}
		}
	}

	ll ans=0;
	each(gr,grs)amax(ans,gr.size());
	each2(ci_C,st,mp){
		auto[ci,C]=ci_C;
		ll bns=grs[ci].size();
		each(CI,st){
			bns+=grs[CI].size();
		}
		amax(ans,bns);
	}
	out(ans);
}
