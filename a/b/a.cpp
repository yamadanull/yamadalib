#include "../../template/multitest-template.hpp"
using namespace yamada;

bool check(vl mexs,multiset<ll> &st,ll cnt){ // stのうちcnt個は使えない
	if(len(st)<cnt)return 0;
	if(mexs.empty())return 1;
	if(Max(mexs)==0){
		return len(st)-cnt>=len(mexs);
	}
	if(st.empty())return 0;
	if(Sum(mexs)>len(st)-cnt)return 0;
	/* err(mexs); */
	/* err(st); */
	vl nexs;
	each(m,mexs)if(m){
		rep(i,m){
			auto it=st.find(i);
			if(it==st.end()){
				nexs.eb(i);
			}
			else{
				if(i==0 || i==1){
					++cnt;
				}
				else st.erase(it);
			}
		}
	}
	each(m,mexs)if(!m)cnt++;
	return check(nexs,st,cnt);
}

void yamada::solve()
{
	IN(N,A=LL*N);
	if(N==1){
		DIE(max<ll>(1,A[0]));
	}
	multiset<ll> st;
	each(a,A)st.insert(a);

	/* check({4},st,0); */
	out(bisearch<ll>(1,1<<18,[&](ll mex){
		auto st2=st;
		return check({mex},st2,0);
	}));
}
