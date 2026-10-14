/* #pragma once */

/* template <typename Mono> */
/* struct SparseTable { */
/* 	int N; */
/* 	vector<vector<Mono>> table; */
/* 	SparseTable() {} */
/* 	SparseTable(const vector<Mono> &v) : N(v.size()) { */
/* 		int b = 1; */
/* 		while ((1 << b) <= N) ++b; */
/* 		table.push_back(v); */
/* 		for (int i = 1; i < b; i++) { */
/* 			table.push_back(vector<Mono>(N, Mono())); */
/* 			for (int j = 0; j + (1 << i) <= N; j++) { */
/* 				table[i][j] = table[i - 1][j] + table[i - 1][j + (1 << (i - 1))]; */
/* 			} */
/* 		} */
/* 	} */
/* 	// [l, r) */
/* 	Mono query(int l, int r) { */
/* 		assert(0 <= l && l <= r && r <= N); */
/* 		if (l == r) return Mono(); */
/* 		int b = 31 - __builtin_clz(r - l); */
/* 		return table[b][l] + table[b][r - (1 << b)]; */
/* 	} */
/* }; */
#pragma once

#include <cassert>
#include <limits>
#include <vector>
using namespace std;

template <typename T>
struct SparseTable {
  inline static constexpr T INF = numeric_limits<T>::max() / 2;
  int N;
  vector<vector<T> > table;
  T f(T a, T b) { return min(a, b); }
  SparseTable() {}
  SparseTable(const vector<T> &v) : N(v.size()) {
    int b = 1;
    while ((1 << b) <= N) ++b;
    table.push_back(v);
    for (int i = 1; i < b; i++) {
      table.push_back(vector<T>(N, INF));
      for (int j = 0; j + (1 << i) <= N; j++) {
        table[i][j] = f(table[i - 1][j], table[i - 1][j + (1 << (i - 1))]);
      }
    }
  }
  // [l, r)
  T query(int l, int r) {
    assert(0 <= l and l <= r and r <= N);
    if (l == r) return INF;
    int b = 31 - __builtin_clz(r - l);
    return f(table[b][l], table[b][r - (1 << b)]);
  }
};

/**
 * @brief Sparse Table
 */
