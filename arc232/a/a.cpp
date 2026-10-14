#include "../../template/multitest-template.hpp"
#include "../../segment-tree/lazy-segment-tree-utility.hpp"
using namespace yamada;

bool naive(int N,vc<int> A,vc<int> B){
	FOR(msk,1<<N){
		bool bns=1;
		FOR_E(l,r,Zip(A,B)){
			int cnt=0;
			FOR(i,l,r)if(msk>>i&1)++cnt;
			if(cnt!=2)bns=0;
		}
		if(bns)return 1;
	}
	return 0;
}

vc<int> cal_fn(int N,vc<int> A,vc<int> B){ // 右側の禁止のみ
	int M=len(A);
	Sort(Zip(A,B));
	for(int l=0,r=0; l<M; l=r){
		while(r<M && A[l]==A[r])++r;
		Reverse(B.begin()+l,B.begin()+r);
	}

	updatemax_lazyseg<int> segfn(vc<int>(N,0));
	min_segtree<int> seg(B);
	for(int l=0,r=0; l<M; l=r){
		while(r<M && A[l]==A[r])++r;
		int mnb=seg(l,M);
		segfn.apply(mnb,B[l],1);
	}
	return segfn.get();
}

bool cal(int N,vc<int> A,vc<int> B){
	vc<int> fn=[&]()->vc<int>{
		auto C=B|Transform([&](int b){return N-b;})|rtov;
		auto D=A|Transform([&](int a){return N-a;})|rtov;
		vc<int> ans(N);
		FOR_E(f,g,h,Zip(ans,cal_fn(N,A,B),cal_fn(N,C,D)|Rev))f=g|h;
		return ans;
	}();
	if(!Contains(fn,1)){
		FOR_E(a,b,Zip(A,B))if(b-a<2)return 0;
		return 1;
	}
	{
		vc<int> cmp;
		FOR_E(i,f,fn|Enumerate)if(!f)cmp.eb(i);
		FOR_E(a,A)a=lb(cmp,a);
		FOR_E(a,B)a=lb(cmp,a);
		Sort(Zip(A,B));
		vc<int> C,D;
		for(int l=0,r=0; l<len(A); l=r){
			while(r<len(A) && A[l]==A[r] && B[l]==B[r])++r;
			C.eb(A[l]);
			D.eb(B[l]);
		}
		A=C;
		B=D;
		N=len(cmp);
	}
	return cal(N,A,B);
}

void yamada::solve()
{
	INT(N,M);
	vc<int> A(M),B(M); ZIN(A,B);
	FOR_E(l,A)--l;

	/* { */
	/* 	bool a=naive(N,A,B); */
	/* 	bool b=cal(N,A,B); */
	/* 	if(a!=b){ */
	/* 		ERR(a,b); */
	/* 		ERR(A); */
	/* 		ERR(B); */
	/* 		assert(0); */
	/* 	} */
	/* } */
	YesNo(cal(N,A,B));
}
