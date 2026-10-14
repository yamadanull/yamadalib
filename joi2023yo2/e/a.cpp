#include "../../template/template.hpp"
#include "../../segment-tree/lazy-segment-tree-utility.hpp"
using namespace yamada;

using T=tuple<ll,ll,ll>;
using E=ll;
T f(T a,T b){
	if(get<0>(a)!=get<0>(b))return max(a,b);
	ll ans=-infLL,bns=infLL,cns=-infLL;
	rep(2){
		swap(a,b);
		auto[x,y,z]=a;
		amax(ans,x);
		amin(bns,y);
		amax(cns,z);
	}
	return {ans,bns,cns};
}
T g(T a,E f){get<0>(a)+=f; return a;}
E h(E f,E g){return f+g;}
T ti(){return {-infLL,infLL,-infLL};}
E ei(){return 0;}

void yamada::solve()
{
	inl(N,Q);
	vl A(N); in(A);
	V<bool> fn(N);

	V<T>init(N);
	{
		UpdateMax_LazySegmentTree<ll,-infLL> seg(A);
		rep(i,N){
			if(seg.query(0,i)<=A[i])fn[i]=true;
			if(seg.query(i,N)<=A[i])fn[i]=true;
		}
		rep(i,N){
			if(fn[i]){
				init[i]=mkt(A[i],i,i);
			}
			else{
				ll a=infLL;
				amin(a,seg.query(0,i));
				amin(a,seg.query(i,N));
				init[i]=mkt(a,i,i);
			}
		}
	}

	LazySegmentTreeBase<T,E,f,g,h,ti,ei> seg(init);

	while(Q--){
		inl(op);
		if(op==1){
			inl(R);
			auto[a,l,r]=seg.query();
			amin(R,r+1);
			seg.update(0,R,-1);
		}
		else if(op==2){
			inl(L); L=N-L;
			auto[a,l,r]=seg.query();
			amax(L,l);
			seg.update(L,N,-1);
		}
		else{
			inl(i); --i;
			ll ans=get<0>(seg.get_val(i));
			if(!fn[i])amin(ans,A[i]);
			out(ans);
		}
		while(1){
			auto[a,i,j]=seg.query();
			bool end=true;
			rep(2){
				swap(i,j);
				if(A[i]<a){
					seg.update_val(i,-1);
					end=false;
				}
			}
			if(end)break;
		}
		rep(i,N)cout<<get<0>(seg.get_val(i))<<(i==N-1? "\n":" ");
	}
}
