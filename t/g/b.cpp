#include "../../template/template.hpp"
#include "../../prime/fast-factorize.hpp"
#include "../../segment-tree/lazy-segment-tree-utility.hpp"
using namespace yamada;

void tc()
{
	inl(N);
	vl ans(N);

	// seg[i]個消すとgcdの素因数iの数が増える
	AddMin_LazySegmentTree<ll,infLL> seg(vl(N+1,0));
	vl cnt(N+1,infLL);

	// gcdを素因数分解したもの
	set<ll> st; rep(i,1,N+1)if(is_prime(i))st.insert(i);
	ll gcd=0;
	rep(i,N){
		inl(a);
		ll ngcd=__gcd(a,gcd);

		seg.update(0,N+1,1);
		if(ngcd==gcd){
			auto pc=factor_count(a);
			each2(p,c,pc){
				if(c>cnt[p]){
					// 素因数pを削除するときにaを消さなくて済む
					seg.update_val(p,-1);
				}
			}

		}
		else{
			auto pc=factor_count(a);
			/* seg.update(0,N+1,1); */
			each2(p,c,pc){
				if(c>cnt[p]){
					// 素因数pを削除するときにaを消さなくて済む
					seg.update_val(p,-1);
				}
				if(c<cnt[p]){
					// 素因数pを削除するときにaを消すだけでいい
					seg.update_val(p,1-seg.get_val(p));
					amin(cnt[p],c);
				}
			}

			auto pc2=factor_count(ngcd);
			set<ll> nst; each2(p,c,pc2)nst.insert(p);
			each(p,st)if(nst.find(p)==nst.end()){
				seg.update_val(p,1-seg.get_val(p));
				cnt[p]=0;
			}
			st=nst;
		}

		/* if(i==0)each(c,cnt)if(c==infLL)c=0; */
		/* out(i,":",cnt); */
		out(i,"seg:");
		rep(i,N+1)cout<<seg.get_val(i)<<(i==N? "\n":" ");
		gcd=ngcd;
		ans[i]=i+1-seg.query(0,N+1);
		/* out(i,gcd,seg.query(0,N+1)); */
	}
	out(ans);
}
void yamada::solve() { inl(T); while(T--)tc(); }
