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
			if(!fn)out(cur);
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
	/* inl(N); */
	/* ll ans=0; */
	/* vl cur; */
	/* vv(ll,A,N,N*N); */
	vvl A;
	A.eb(vl{1,1,1,1,1,1,1,1,1});
	A.eb(vl{1,1,1,0,0,0,0,0,0});
	A.eb(vl{0,0,0,2,2,2,2,2,2});
	out(check(3,A));

/* 	while(1){ */
/* 		/1* out(); *1/ */
/* 		rep(i,N)rep(j,N*N)A[i][j]=randint(0,N); */
/* 		if(check(N,A)){ */
/* 			/1* out("OKOKOKOKOK"); *1/ */
/* 			/1* each(a,A)out(a); *1/ */

/* 			ll cnt=0; */
/* 			ll dnt=0; */
/* 			rep(j,N*N){ */
/* 				set<ll>st; */
/* 				rep(i,N)st.insert(A[i][j]); */
/* 				if(st.size()<=2){ */
/* 					++cnt; */
/* 					if(st.size()==1)++dnt; */
/* 				} */
/* 			} */
/* 			/1* out(cnt,dnt); cout.flush(); *1/ */
/* 			assert(cnt<=2); */
/* 			/1* out("OKOKOKOKOKOK:"); *1/ */
/* 			/1* each(a,A)out(a); *1/ */
/* 			if(cnt==3){ */
/* 				break; */
/* 			} */
/* 		} */
/* 		else{ */
/* 			ll cnt=0,dnt=0; */
/* 			rep(j,N*N){ */
/* 				set<ll>st; */
/* 				rep(i,N)st.insert(A[i][j]); */
/* 				if(st.size()<=2){ */
/* 					++cnt; */
/* 					if(st.size()==1)++dnt; */
/* 				} */
/* 			} */
/* 			if(cnt==2 && dnt==0){ */
/* 				out("NG:",cnt); */
/* 				each(a,A)out(a); */
/* 			} */
/* 			/1* out("NG"); *1/ */
/* 			/1* each(a,A)out(a); *1/ */
/* 		} */
/* 		cout.flush(); */
/* 	} */
}
