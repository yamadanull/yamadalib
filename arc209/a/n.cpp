#include "../../template/template.hpp"
using namespace yamada;

void tc()
{
	ins(S); inl(K);
	ll N=S.size();

	vl A(N);
	rep(i,N)A[i]=(S[i]=='('? 1:-1);
	A=mkrui(A);
	AddMin_LazySegmentTree<ll,infLL> seg(A);
	if(seg.query()<0)die("First");
	if(A.back()!=0)die("First");
	if(K%2)die("First");

	// カッコ列上の半壊区間、累積和上の閉区間
	ll L=0,R=N;
	while(R-L>K && seg.query(L+1,R)>0){
		++L; --R;
		seg.update(L,R+1,-1);
	}
	if(R-L==K)die("Second");

	// [L,R)まで削った(まだ正しいカッコ列、足がついている部分がある
	vl pos;
	rep(i,L,R+1)if(seg.get_val(i)==0)pos.eb(i);
	vl siz;
	rep(i,pos.size()-1)siz.eb(pos[i+1]-pos[i]);

	// サイズ4以上にたどり着いたときの文字の最長の長さ
	ll len=-infLL;
	CumulativeSum cum(siz);
	ll n=siz.size();
	rep(i,siz.size())if(siz[i]>=4){
		amax(len,R-L-cum.query(0,i));
		amax(len,R-L-cum.query(i+1,n));
	}

	out(len-2>=K? "First":"Second");
}
void yamada::solve() { inl(T); while(T--)tc(); }
