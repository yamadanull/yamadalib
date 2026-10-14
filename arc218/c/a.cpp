#include "../../template/template.hpp"
using namespace yamada;

bool check(vvl A,vl Q,vl ans){
	ll N=Q.size();
	if(ans.size()>N*N*2)return 0;
	vl R(N); rep(i,N)R[i]=i;
	each(i,ans){
		auto p=A[i];
		vl nB(N);
		rep(j,N)nB[j]=R[p[j]];
		R=nB;
	}
	/* out("Q:",Q); */
	/* out("R:",R); */
	/* cout.flush(); */
	return R==Q;
}

// 右シフト
void shift(vl& A,ll L,ll R,ll cnt){
	auto B=A;
	rep(i,L,R){
		if(inLR(L,i,R)){
			ll I=i+cnt;
			if(I>=R)I-=R-L;
			B[I]=A[i];
		}
	}
	A=B;
}

void yamada::solve()
{
	inl(N);
	vvl A;
	{
		vl a(N); rep(i,N)a[i]=i;
		shift(a,0,2,1);
		A.eb(a);
		shift(a,0,2,1);

		shift(a,1,N,1);
		A.eb(a);
	}

	// 1:右シフトが可能
	out(2);
	each(a,A){
		each(e,a)++e;
		out(a);
		each(e,a)--e;
	}
	cout.flush();

	vl Q(N); in(Q); each(q,Q)--q;

	vl R(N); rep(i,N)R[i]=i;
	vl ans;
	// from,toは添字
	auto mov=[&](ll from,ll to)->void{
		auto Rshift=[&](ll cnt)->void{
			shift(R,1,N,cnt);
			rep(cnt)ans.eb(1);
		};
		auto Lshift=[&](ll cnt)->void{
			Rshift(N-1-cnt);
		};
		auto swap01=[&]()->void{
			swap(R[0],R[1]);
			ans.eb(0);
		};
		assert(to<from);

		Lshift(from-1);
		if(to==1)return;
		swap01();
		if(to==0)return; // from にQ0が埋め込まれた
		Rshift(from-to);
		swap01(); // toに答えが排他t
		Lshift(from-to);
		swap01(); // Q0を回収、1にはfrom
		Rshift(from-1);
	};

	rep(i,N-1)if(R[i]!=Q[i]){
		rep(j,i+1,N)if(R[j]==Q[i]){
			mov(j,i);
			/* out("Q:",Q); */
			/* out("R:",R); */
			/* cout.flush(); */
			assert(R[i]==Q[i]);
			break;
		}
	}
	assert(Q==R);

	each(a,ans)++a;
	out(ans.size(),ans);
	each(a,ans)--a;
	cout.flush();

	assert(check(A,Q,ans));
}
