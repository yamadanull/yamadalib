#include "../../template/multitest-template.hpp"

void yamada::solve()
{
	inl(N);
	auto query=[&](ll msk,ll nsk)->VV<bool>{
		vv(bool,Brow,N,N-1); // 差分
		vv(bool,Bcol,N-1,N); // 差分
		rep(i,N)rep(j,N-1){
			Brow[i][j]=(nsk>>j&1)^i&1;
		}
		rep(j,N)rep(i,N-1){
			Bcol[i][j]=(msk>>i&1)^j&1;
		}
		vv(bool,A,N,N);
		rep(i,N)rep(j,N){
			if(i&&j){
				bool a=(Brow[i][j-1]? !A[i][j-1]:A[i][j-1]);
				bool b=(Bcol[i-1][j]? !A[i-1][j]:A[i-1][j]);
				if(a!=b)return{};
				A[i][j]=a;
			}
			else if(i){
				bool a=(Bcol[i-1][j]? !A[i-1][j]:A[i-1][j]);
				A[i][j]=a;
			}
			else if(j){
				bool a=(Brow[i][j-1]? !A[i][j-1]:A[i][j-1]);
				A[i][j]=a;
			}
		}
		return A;
	};

	ll cnt=0,dnt=0;
	rep(msk,1<<N-1)rep(nsk,1<<N-1){
		auto A=query(msk,nsk);
		if(A.empty())continue;
		++cnt;
		set<ll> st;
		rep(2){
			A=Rotate(A);
			rep(i,N){
				ll cnt=0;
				rep(j,N){
					cnt+=A[i][j];
				}
				st.insert(cnt);
			}
		}

		if(st.size()!=1)continue;
		/* { */
		/* 	assert(*st.begin()==N/2); */
		/* 	ll di=-1,dj=-1; */
		/* 	rep(i,0,N,2)rep(j,0,N,2){ */
		/* 	} */
		/* } */
		++dnt;

		vs ans(N);
		rep(i,N)rep(j,N){
			ans[i]+=A[i][j]? '#':'.';
		}

		out();
		out();
		each(a,ans)out(a);
		rep(di,2)rep(dj,2){
			out();
			vs bns(N/2);
			rep(i,di,N,2)rep(j,dj,N,2){
				bns[i/2]+=A[i][j]? '#':'.';
			}
			each(b,bns)out(b);
		}
	}
	out("cnt,dnt:",cnt,dnt);
}
