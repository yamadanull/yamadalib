#include "../../template/template.hpp"
using namespace yamada;

template <size_t X = 2, char margin = 0>
struct SimpleTrie {
	struct Node {
		array<int, X> nxt;
		int val;
		Node() : val(0) { fill(nxt.begin(), nxt.end(), -1); }
	};
	std::vector<Node> st;
	SimpleTrie() { st.emplace_back(); }
	inline int &next(int i, int j) { return st[i].nxt[j]; }

	template <typename T>
	void add(std::vector<T> s, int val) {
		int pos = 0;
		for (int i = 0; i < (int)s.size(); i++) {
			amax(st[pos].val, val);
			int k = s[i] - margin;
			if (~next(pos, k)) {
				pos = next(pos, k);
				continue;
			}
			int npos = st.size();
			next(pos, k) = npos;
			st.emplace_back();
			pos = npos;
		}
		amax(st[pos].val,val);
	}
};

const int LG=3; // 
void yamada::solve()
{
	inl(N,K);
	vl A(N); in(A);
	auto tovb=[&](ll a)->vb{
		vb ans(LG);
		repr(t,LG)ans[t]=a>>t&1;
		reverse(all(ans));
		return ans;
	};

	SimpleTrie trie;
	rep(i,N){
		ll pos=0;
		ll val=0;
		repr(t,LG){
			if(K>>t&1){
				if(A[i]>>t&1){ // 相手は０、全１
					ll u=trie.next(pos,1);
					if(u>=0)amax(val,trie.st[u].val);
					pos=trie.next(pos,0);
				}
				else{ // 相手は１，全０
					ll u=trie.next(pos,0);
					if(u>=0)amax(val,trie.st[u].val);
					pos=trie.next(pos,1);
				}
			}
			else{
				if(A[i]>>t&1){ // 相手は１
					pos=trie.next(pos,1);
				}
				else{ // 相手は０
					pos=trie.next(pos,0);
				}
			}
			if(pos<0)break;
		}
		if(pos>=0)amax(val,trie.st[pos].val);
		/* err(i,val); */

		trie.add(tovb(A[i]),val+1);
		/* rep(u,trie.st.size()){ */
		/* 	err(u,trie.st[u].nxt,trie.st[u].val); */
		/* } */
	}
	out(trie.st[0].val);
}
