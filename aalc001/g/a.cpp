T G(T X,E A,ll){
	T ans{};
	FOR(i,K)FOR(j,i+1){
		mint bns=binom(i,j)*X[j];
		FOR(i-j)bns*=A;
		ans[i]+=bns;
	}
	return ans;
}
E H(E a,E b){
	return a+b;
}
T genT(ll a){
	T ans;
	mint cur=1;
	FOR(i,K)ans[i]=cur,cur*=a;
	return ans;
}
using AM=MyActedMonoid<T,E,F,G,H,ti,ei>;

void yamada::solve()
{
	LL(N,Q);
	vl A(N); IN(A);
	LazySegmentTree<AM> seg(A|Transform([](auto a)->T{
		return genT(a);
	})|rtov);
	FOR(Q){
		LL(op);
		if(op==1){
			LL(l,r,x); --l;
			seg.apply(l,r,x);
		}
		else{
			LL(l,r,k); --l;
			OUT(seg(l,r)[k]);
		}
	}
}
