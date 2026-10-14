#include "../../template/template.hpp"
#include "../../misc/all.hpp"
using namespace yamada;

ll dist(vl A,vl B){
	ll ans=0;
	rep(i,A.size())if(A[i]!=B[i])++ans;
	return ans;
}

bool check(ll N,vvl A){
	vl cur;
	auto dfs=[&](auto&& self)->bool{
		if(cur.size()==N*N){
			bool fn=false;
			each(a,A)if(dist(cur,a)>=N*N-N){
				fn=true;
				break;
			}
			return fn;
		}
		rep(i,N){
			cur.eb(i);
			if(!self(self))return false;
			cur.pop_back();
		}
		return true;
	};
	return dfs(dfs);
}

void yamada::solve()
{
	inl(N);
	ll ans=0;
	vl cur;
	vv(ll,A,N,N*N);

	while(1){
		rep(i,N)rep(j,N*N)A[i][j]=randint(0,N);
		if(check(N,A)){
			ll cnt=0;
			ll dnt=0;
			rep(j,N*N){
				set<ll>st;
				rep(i,N)st.insert(A[i][j]);
				if(st.size()<=2){
					++cnt;
					if(st.size()==1)++dnt;
				}
			}
			assert(cnt<=2);
			if(cnt==3){
				break;
			}
		}
		else{
			ll cnt=0,dnt=0;
			rep(j,N*N){
				set<ll>st;
				rep(i,N)st.insert(A[i][j]);
				if(st.size()<=2){
					++cnt;
					if(st.size()==1)++dnt;
				}
			}
			if(cnt==2){
				out();
				out("NG:",cnt);
				each(a,A)out(a);
				cout.flush();
			}
		}
	}
}
