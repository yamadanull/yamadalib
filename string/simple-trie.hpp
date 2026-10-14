#pragma once

// 提出用ファイルにコピペして書き足して使うことが多そう？
template <size_t X = 26, char margin = 'a'>
struct SimpleTrie {
	struct Node {
		array<int, X> nxt;
		int cnt;
		Node() : cnt(0) { fill(nxt.begin(), nxt.end(), -1); }
	};
	std::vector<Node> st;
	SimpleTrie() { st.emplace_back(); }
	inline int &next(int i, int j) { return st[i].nxt[j]; }

	template <typename T>
	void add(std::vector<T> &s, int cnt = 1) {
		int pos = 0;
		for (int i = 0; i < (int)s.size(); i++) {
			st[pos].cnt += cnt;
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
		st[pos].cnt += cnt;
	}
};
