#include "../../template/template.hpp"
#include "../../data-structure/rollback-union-find.hpp"
#include "../../segment-tree/segment-tree-divide-and-conquer.hpp"
#include "../../segment-tree/lazy-segment-tree.hpp"
#include "../../monoid/make-monoid.hpp"
using namespace yamada;

using T=array<bool,2>;
using E=bool;
T ti(){return{0,0};}
E ei(){return 0;}
T F(T a,T b){
	a[0]|=b[0];
	a[1]|=b[1];
	return a;
}
T G(T a,E f){ if(f)swap(a[0],a[1]); return a; }
E H(E f,E g){return f^g;}
using AM=MyActed<T,E,F,G,H,ti,ei>;

void yamada::solve()
{
	ini(N,M,Q);
	V<T> init(N);
	rep(i,N){
		inl(a);
		init[i][a%2]=1;
		init[i][!(a%2)]=0;
	}

	LazySegmentTree<AM> seg(init);
	auto get=[&](int pos)->bool{ return (seg.get(pos).a)[1]; };
	auto pre_x=[&](int pos)->int{ // 距離 M+1 以上離れている
		if(pos<=M)return -1;
		auto x=get(pos);
		return seg.min_left(pos-M,[&](T sm){return !sm[x];})-1;
	};
	auto pre_b=[&](int pos,bool x)->int{ // 距離の制約はない
		return seg.min_left(pos,[&](T sm){return !sm[x];})-1;
	};
	auto nxt_b=[&](int pos,bool x)->int{ // 距離の制約はない
		return seg.max_right(pos+1,[&](T sm){return !sm[x];});
	};
	auto get_umv=[&](int m,V<P<int,int>>& A)->void{
		if(m==0 || m>=N)return;
		rep(x,2){
			int pos=nxt_b(m,x);
			while(pos<N){
				int lpos=pre_x(pos);
				if(lpos>=0){
					if(lpos>=m)break;
					A.eb(lpos,pos);
				}
				pos=nxt_b(pos,x);
			}
		}
	};

	VV<P<int,int>> add(Q+1),del(Q+1); // add query
	VV<tuple<int,int,bool,int>> lrx_oi(Q+1); // cal query
	V<int> ans;
	{
		rep(i,N){
			int j=pre_x(i);
			/* out("j,i:",j,i); */
			if(j>=0)add[0].eb(j,i);
		}

		V<array<int,3>> qs;
		while(Q--){
			ini(op); --op;
			if(op==0){
				ini(l,r); --l; inl(x);
				if(x%2==0)continue;
				qs.eb(array<int,3>{0,l,r});
			}
			else{
				ini(l,r); --l;
				qs.eb(array<int,3>{1,l,r});
			}
		}
		Q=qs.size();
		/* out("Q:",Q); */

		int OI=0;
		int TIM=0;
		for(int ql=0,qr=0; ql<Q; ql=qr){
			/* fout("ql,qr,Q:",ql,qr,Q); */
			/* fout("add:",add); */
			while(qr<Q && qs[ql][0]==qs[qr][0])++qr;
			/* fout("ql,qr,Q:",ql,qr,Q); */
			if(ql>0 && !qs[ql][0])TIM++;

			if(qs[ql][0]==0){
				rep(qi,ql,qr)each(m,qs[qi]){
					if(m==0)continue;
					get_umv(m,del[TIM]);
					seg.apply(0,m,1);
					get_umv(m,add[TIM]);
				}
			}
			else{
				rep(qi,ql,qr){
					auto[op,l,r]=qs[qi];
					get_umv(l,del[TIM]);
					get_umv(r,del[TIM]);
					lrx_oi[TIM].eb(l,r,get(l),OI++);
					get_umv(l,add[TIM+1]);
					get_umv(r,add[TIM+1]);
				}
			}
		}
		ans.resize(OI,1);
	}

	int TIM=add.size();
	rep(t,TIM)fout(t,"add:",add[t]);
	rep(t,TIM)fout(t,"del:",del[t]);
	each(es,add)es=mkuni(es);
	each(es,del)es=mkuni(es);
	rep(t,TIM)fout(t,"add:",add[t]);
	rep(t,TIM)fout(t,"del:",del[t]);

	using U = P<int,int>;
	SegmentTreeDAC<U> dac(TIM);
	// (calc query range, declarate info, exc...)
	{
		map<P<int,int>,int> mp;
		rep(t,TIM){
			each(e,add[t]){
				mp[e]=t;
			}
			each(e,del[t]){
				assert(mp.count(e));
				dac.add_query(mp[e],t,e);
				mp.erase(e);
			}
		}
		each2(e,t,mp)dac.add_query(t,TIM,e);
	}

	RollbackUnionFind uf(N);
	auto add_q = [&](U laz)->void{ uf.unite(laz.fi,laz.se); };
	auto get_time = [&]()->int{ return uf.get_state(); };
	auto rollback = [&](int time)->void{ uf.rollback(time); };
	auto query = [&](int qi)->void{
		for(auto&[l,r,x,oi]:lrx_oi[qi])if(x){
			int m=pre_b(r,1);
			assert(m>=0);
			if(uf.same(l,m))ans[oi]=2;
		}
	};
	dac.run(add_q, get_time, rollback, query);
	each(a,ans)out(a);
}
