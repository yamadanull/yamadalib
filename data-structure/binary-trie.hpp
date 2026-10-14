#pragma once
#include "node-pool.hpp"

// verify: https://judge.yosupo.jp/submission/383104
// 桁 LOG のビットが立っている要素を追加してはいけない
// T: value type, C: size type
// 非永続ならば、2 * 要素数 のノード数
// bit_i: 桁 bit_i 以上が決まっているみたいな状態を表現
template <typename T, int LOG = 30, typename U = int, bool PERSISTENT = false>
struct BinaryTrie {
	struct Node {
		int wid; // 親へのxorの桁数
		T val; // 親へのxor
		U cnt;
		std::array<Node*, 2> nxt;
	};

	NodePool<Node> pool;
	void reset() { pool.reset(); }
	Node* new_root() { return nullptr; }

	// f(val, cnt)
	template <typename F>
	void enumerate(Node* root, F f) {
		auto dfs = [&](auto &dfs, Node* root, T val, int bit_i) -> void {
			if (bit_i == 0) { f(val, root->cnt); return; }
			for (auto& c : root->nxt) if (c) {
				dfs(dfs, c, val << c->wid | c->val, bit_i - c->wid);
			}
		};
		if (root) dfs(dfs, root, 0, LOG);
	}

	Node* add(Node* root, T val, U cnt = 1) {
		if (!root) root = new_node(0, 0);
		assert((val >> LOG) == 0);
		return _add(root, LOG, val, cnt);
	}

	// xor_val したあとの値で昇順 K 番目
	T kth_element(Node* root, U K, const T& xor_val = 0) {
		assert(root && K < root->cnt);
		return _kth_element(root, 0, K, LOG, xor_val) ^ xor_val;
	}
	T min_element(Node* root, const T& xor_val = 0) { return kth_element(root, 0, xor_val); }
	T max_element(Node* root, const T& xor_val = 0) { return kth_element(root, root->cnt - 1, xor_val); }

	// xor_val したあとの値で [0, upper) 内に入るものの個数
	U count_lower(Node* root, T upper, const T& xor_val = 0) {
		if (!root) return 0;
		return _count_lower(root, LOG, upper, xor_val, 0);
	}
	U count_upper(Node* root, T lower, const T& xor_val = 0) {
		if (!root) return 0;
		return root->cnt - _count_lower(root, LOG, lower, xor_val, 0);
	}

	// xor_val したあとの値で [lower, upper) 内に入るものの個数
	U count(Node* root, T lower, T upper, const T& xor_val = 0) {
		return count_lower(root, upper, xor_val) - count_lower(root, lower, xor_val);
	}
	U count(Node* root, T X, const T& xor_val = 0) {
		return count_lower(root, X + 1, xor_val) - count_lower(root, X, xor_val);
	}

	private:
	Node* new_node(int wid, T val, U cnt = 0) {
		Node* n = pool.create();
		for (auto& c : n->nxt) c = nullptr;
		n->wid = wid, n->val = val, n->cnt = cnt;
		return n;
	}

	Node* clone(Node* c) {
		if (!c || !PERSISTENT) return c;
		return pool.clone(c);
	}

	inline T mask(int K) { return (T(1) << K) - 1; }
	inline int bit_length(int mx, T val) {
		for (int t = mx - 1; t >= 0; t--) if (val >> t & 1) return t + 1;
		return 0;
	}
	Node* _add(Node* root, int bit_i, T val, U cnt) {
		root = clone(root);
		root->cnt += cnt;
		if (bit_i == 0) return root;

		bool cld_i = val >> bit_i - 1 & 1;
		Node* c = root->nxt[cld_i];
		if (!c) {
			root->nxt[cld_i] = new_node(bit_i, val, cnt);
			return root;
		}
		int W = c->wid;
		if (val >> bit_i - W == c->val) {
			root->nxt[cld_i] = _add(c, bit_i - W, val & mask(bit_i - W), cnt);
			return root;
		}
		int W0 = bit_length(W, val >> bit_i - W ^ c->val); // deep
		int W1 = W - W0; // narrow
		int bit_j = bit_i - W1; // mid
		bool cld_j = val >> bit_j - 1 & 1;

		Node* n = new_node(W1, c->val >> W0, c->cnt + cnt); // mid
		c = clone(c); // deep
		c->wid = W0;
		c->val &= mask(W0);

		n->nxt[!cld_j] = c;
		n->nxt[cld_j] = new_node(bit_j, val & mask(bit_j), cnt);
		root->nxt[cld_i] = n;
		return root;
	}

	T _kth_element(Node* root, T val, U K, int bit_i, const T& xor_val) {
		if (bit_i == 0) return val;
		Node* L_ptr = root->nxt[0]; Node* R_ptr = root->nxt[1];
		if (xor_val >> bit_i - 1 & 1) std::swap(L_ptr, R_ptr);
		U L_cnt = (L_ptr ? L_ptr->cnt : 0);
		Node* c;
		if (K < L_cnt) c = L_ptr;
		else c = R_ptr, K -= L_cnt;
		int W = c->wid;
		return _kth_element(c, val << W | c->val, K, bit_i - W, xor_val);
	}

	U _count_lower(Node* root, int bit_i, const T& M, const T& xor_val, T val) {
		{
			T now = val ^ xor_val >> bit_i;
			if (M >> bit_i > now) return root->cnt;
			if (bit_i == 0 || M >> bit_i < now) return 0;
		}
		U res = 0;
		for (auto& c : root->nxt) if (c) {
			res += _count_lower(c, bit_i - c->wid, M, xor_val, val << c->wid | c->val);
		}
		return res;
	}
};
