#include "../../template/multitest-template.hpp"
#include "../../segment-tree/segment-tree.hpp"
#include "../../monoid/generate-monoid.hpp"
using namespace yamada;

/* const int N_MAX=150'000; */
/* int A[N_MAX],B[N_MAX]; */
using T0=array<array<bool,2>,2>;
using T=tuple<int,int,int,int,T0>;

T0 t0i(){ T0 ans; rg::fill(ans|join,0); return ans; }
T ti(){ return{-1,-1,-1,-1,t0i()}; }

T F(T X,T Y){
	if(X==ti())return Y;
	if(Y==ti())return X;
	auto[al,bl,ar,br,f0]=X;
	auto[aL,bL,aR,bR,f1]=Y;
	T0 ans=t0i();

	rep(fr,2)rep(fL,2){
		{
			array<ll,2> ds{infLL,infLL};
			array<ll,2> as{ar,aL};
			array<ll,2> bs{br,bL};
			array<ll,2> ps{ar+br*(fr?1:-1),aL+bL*(fL?1:-1)};
			each(d,a,zip(ds,as))each(p,ps)amin(d,abs(a-p));
			if(Any(zip(ds,bs),[](auto db){
				auto[d,b]=db;
				return d!=b;
			}))continue;
		}
		if(bl==7)err(fr,fL);
		rep(fl,2)if(f0[fl][fr])rep(fR,2)if(f1[fL][fR])ans[fl][fR]=1;
	}
	return{al,bl,aR,bR,ans};
}
using Mono=MyMonoid<T,F,ti>;
T genT(ll a,ll b){
	auto ans=t0i();
	if(b)rep(i,2)ans[i][i]=1;
	else rg::fill(ans|join,1);
	return{a,b,a,b,ans};
}

void yamada::solve()
{
	inl(N);
	vl A(N),B(N); in(A,B);
	SegmentTree<Mono> seg(zip(A,B)|vtran([&](auto ab)->T{
		auto[a,b]=ab;
		return genT(a,b);
	})|rtov);

	for(int Q=rdi();Q--;){
		{
			inl(i,s); --i;
			seg.set(i,genT(A[i],B[i]=s));
		}
		if(N==3 && Q==0){
			rep(l,N)rep(r,l+1,N+1)err(l,r,Q,get<4>(seg(l,r)));
		}
		auto ans=Any(get<4>(seg())|join,[](auto b){return b;});
		YesNo(ans);
	}
}
