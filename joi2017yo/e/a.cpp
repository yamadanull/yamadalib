#include "../../template/template.hpp"
#include "../../graph/graph-template.hpp"

void yamada::solve()
{
	inl(H,W);
	auto idx=[&](ll i,ll j){return i*W+j;};

	ll N=H*W;
	vl A(N); in(A);
	UnweightedGraph g(N);
	vl di{-1,0,1,0};
	vl dj{0,-1,0,1};
	rep(i,H)rep(j,W){
		rep(x,4){
			ll I=i+di[x];
			ll J=j+dj[x];
			if(!inLR(0LL,I,H))continue;
			if(!inLR(0LL,J,W))continue;
			if(A[idx(i,j)]>A[idx(I,J)]){
				g[idx(i,j)].eb(idx(I,J));
			}
		}
	}

	vl ord(N); rep(i,N)ord[i]=i;
	sort(all(ord),[&](ll x,ll y){return A[x]<A[y];});

	vl memo(N,-1); // 行き先がひとつである場合の行き先
	rep(i,N)if(g[i].empty())memo[i]=i;

	ll ans=0;
	each(u,ord)if(!g[u].empty()){
		set<ll> st;
		each(v,g[u]){
			if(memo[v]<0){
				memo[u]=-1;
				break;
			}
			memo[u]=memo[v];
			st.insert(memo[v]);
		}
		if(memo[u]<0 || st.size()>=2){
			memo[u]=-1;
			++ans;
		}
	}
	out(ans);
}
