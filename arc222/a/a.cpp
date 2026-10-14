#include "../../template/template.hpp"
#include "../../segment-tree/lazy-segment-tree-utility.hpp"
using namespace yamada;

void tc()
{
	inl(N,M);
	vp lr(M); in(lr);
	each2(l,r,lr)--l;
	sort(all(lr),[](pl x,pl y){return x.fi!=y.fi? x.fi<y.fi: x.se>y.se;});
	{
		vp LR;
		each2(l,r,lr){
			if(!LR.empty() && r<=LR.back().se)continue;
			LR.eb(l,r);
		}
		lr=LR;
		M=lr.size();
	}

	vl ans;
	rep(lr[0].fi)ans.eb(0);
	UpdateMin_LazySegmentTree<ll,infLL> used(vl(N,0));
	rep(lri,M){
		// 少なくともlまでは埋めてあることを保証
		auto[l,r]=lr[lri];
		rep(i,ans.size(),r){
			ll val=used.max_right(0LL,[](ll mn){return mn>=1;});
			used.set(val,1);
			ans.eb(val);
		}

		if(lri<M-1){
			auto[L,R]=lr[lri+1];
			if(r<=L){
				rep(i,r,L){
					ans.eb(0);
				}
				used.apply(0,N,0);
			}
			else{
				rep(i,l,L){
					used.set(ans[i],0);
				}
			}
		}
	}
	while(ans.size()<N)ans.eb(0);
	each(a,ans)a++;
	out(ans);
}
void yamada::solve() { ini(T); while(T--)tc(); }
