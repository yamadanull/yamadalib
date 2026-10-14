#pragma once
#include "node-pool.hpp"

// 要素に情報を持たせたい場合、別のデータ構造で処理
// T: value type, C: size type
template <typename T, typename C = int, int LOG = 30, bool PERSISTENT = false>
struct BinaryTrie {
	struct Node {
		Node* nxt[2];
		C cnt;
		int wid;
		T val;
		Node() {}
	};

	NodePool<Node> pool;
	Node* ROOT;

	void reset() { pool.reset(); }
	Node* new_root() { return nullptr; }

	private:
	Node* _add(T x, const C &cnt, int bit_idx, Node* n) {
		n = clone(n);
		n->cnt += cnt;
		if (bit_idx == -1) return n;
		if (!n->nxt[x >> bit_idx & 1]) {
			n->nxt[x >> bit_idx & 1] = new_node(val, cnt);
			return n;
		}
	}
	public:
	void add(const T &x, int cnt = 1, Node* root = ROOT) {
		if (!root) root = new_node();
		root = _add(x, id, root, LOG);
	}

	private:
	U _find(const T &x, Node* n, int bit_idx) {
		if (bit_idx == -1)
			return n->cnt;
		else {
			if ((LAZY >> bit_idx & 1) == (x >> bit_idx & 1))
				return _find(x, n->nxt[0], bit_idx - 1);
			else
				return _find(x, n->nxt[1], bit_idx - 1);
		}
	}

	public:
	U find(const T &x, Node* root = ROOT) { return _find(x, root, LOG); }

	private:
	T _get_kth(Node* n, int64_t k, int bit_idx) {
		if (bit_idx == -1) return T(0);
		int cnt0 = n->nxt[LAZY >> bit_idx & 1]->cnt;
		if (cnt0 < k) {
			return _get_kth(n->nxt[~LAZY >> bit_idx & 1], k - cnt0, bit_idx - 1) | T(1) << bit_idx;
		}
		return _get_kth(n->nxt[LAZY >> bit_idx & 1], k, bit_idx - 1);
	}

	public:
	T get_kth(int64_t k) { return _get_kth(root, k, LOG); }
	T max_element() { return _get_kth(root, 0, LOG); }
	T min_element() { return _get_kth(root, root->cnt - 1, LOG); }

	private:
	int _count_lower(Node* n, T X, int bit_idx) {
		if (bit_idx == -1) return T(0);
		if (X >> bit_idx & 1) {
			int ans = 0;
			ans += n->nxt[LAZY >> bit_idx & 1]->cnt;
			return ans + _count_lower(n->nxt[~LAZY >> bit_idx & 1], X, bit_idx - 1);
		}
		return _count_lower(n->nxt[LAZY >> bit_idx & 1], X, bit_idx - 1);
	}

	public:
	int count_lower(T X) { return _count_lower(root, X, LOG); }
	int count_upper(T X) { return root->cnt - _count_lower(root, X, LOG); }
	void operate_xor(T x) { LAZY ^= x; }

	private:
	Node* clone(Node* c) {
		if (!c || !PERSISTENT) return c;
		return pool.clone(c);
	}

	Node* new_node(T val, int cnt = 0) {
		Node* u = pool.create();
		u->nxt[0] = u->nxt[1] = nullptr;
		u->val = val;
		u->cnt = cnt;
		if (id != -1) u->accept.emplace_back(id);
		return u;
	}
};
