#include "../../template/template.hpp"
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
	set<multiset<vl>> ok,ng;
	auto dfs=[&](auto&& self)->void{
		if(cur.size()==N*N*N){
			rep(i,N*N*N)A[i/(N*N)][i%(N*N)]=cur[i];

			multiset<vl> st;
			each(a,Transpose(A))st.insert(a);
			if(check(N,A)){
				++ans;
				/* out("OKOKOKOKOK"); */
				/* each(a,A)out(a); */
				ok.insert(st);
			}
			else{
				/* out("NG"); */
				/* each(a,A)out(a); */
				ng.insert(st);
			}
			return;
		}
		rep(i,N){
			cur.eb(i);
			self(self);
			cur.pop_back();
		}
	}; dfs(dfs);
	out(ans);

	each(st,ok){
		out();
		out("OKOKOKOKOK");
		ll cnt=0;
		each(v,st){
			if(v[0]==v[1])++cnt;
			out(v); cout.flush();
		}
		assert(cnt<=1);
	}
	each(st,ng){
		out();
		out("NG");
		ll cnt=0;
		each(v,st){
			if(v[0]==v[1])++cnt;
			out(v); cout.flush();
		}
		assert(cnt>=2);
	}
}
