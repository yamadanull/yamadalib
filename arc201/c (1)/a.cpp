#include "../../template/template.hpp"
#include "../../modint/montgomery-modint.hpp"
using mint = LazyMontgomeryModInt<998244353>;
using namespace yamada;

template <size_t X = 26, char margin = 'a'>
struct Trie {
	struct Node {
		array<int, X> nxt;
		int Cnt,cnt,par;
		mint DP;
		Node(ll p) :par(p),cnt(0),Cnt(0),DP(0) { fill(nxt.begin(), nxt.end(), -1); }
	};

	vector<Node> st;

	Trie() { st.emplace_back(-1); }

	inline int &next(int i, int j) { return st[i].nxt[j]; }

	void cal(int pos){
		st[pos].DP=0;
		{
			mint dp=1;
			rep(j,2){
				if(next(pos,j)<0)dp=0;
				else dp*=st[next(pos,j)].DP;
			}
			st[pos].DP+=dp;
		}
		{
			mint dp=st[pos].cnt;
			dp*=((mint)2).pow(st[pos].Cnt-1);
			st[pos].DP+=dp;
		}
	}

	void add(const string &s) {
		int pos = 0;
		mint ans=1;
		for (int i = 0; i < (int)s.size(); i++) {
			int k = s[i] - margin;
			if (~next(pos, k)) {
				pos = next(pos, k);
				continue;
			}
			int npos = st.size();
			next(pos, k) = npos;
			st.emplace_back(pos);
			pos = npos;
		}

		++st[pos].cnt;
		while(pos>=0){
			++st[pos].Cnt;
			cal(pos);
			pos=st[pos].par;
		}
	}
};

void yamada::solve()
{
	inl(N);
	Trie<2,'A'>t;
	rep(i,N){
		ins(S);
		t.add(S);
		/* if(i==2){ */
		/* 	out(t.st[0].DP,t.st[1].DP,t.st[2].DP,t.st[3].DP,t.st[4].DP,t.st[5].DP); */
		/* } */
		out(t.st[0].DP);
	}
}
