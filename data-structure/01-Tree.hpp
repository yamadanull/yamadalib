#pragma once
#include "data-structure/union-find.hpp"

struct maroon {
  double val;
  int idx;
  long long zero, one;
  int root, siz;
};

bool operator< (const maroon &X1, const maroon &X2) {
  return X1.val < X2.val;
}
bool operator> (const maroon &X1, const maroon &X2) {
  return X1.val > X2.val;
}

vector<int> maroonTree (int N, vector<long long> &zero, vector<long long> &one, vector<int> &pr) {
  vector<deque<long long> > ord(N);
  priority_queue<maroon, vector<maroon>, less<maroon> > q;
  vector<maroon> dat(N);

  for (int i = 0; i < N; ++i) {
    ord[i].push_back(i);
    if(one[i] > 0) dat[i] = {double(zero[i]) / one[i], i, zero[i], one[i], i, 1};
    else dat[i] = {4e18, i, zero[i], one[i], i, 1};
    q.push(dat[i]);
  }
  
  UnionFind d(N);
  while(!q.empty()) {
    int find = q.top().idx; q.pop();
    int root = dat[find].root;
    if(pr[root] < 0) continue;
    int pr_find = d.find(pr[root]);

    int zero_nw = dat[find].zero + dat[pr_find].zero;
    int one_nw = dat[find].one + dat[pr_find].one;
    double val_nw = one_nw > 0 ? (double)zero_nw / one_nw : 4e18;
    int root_nw = dat[pr_find].root;
    int siz_nw = dat[find].siz + dat[pr_find].siz;


    //unite DSU
    d.unite(find, pr_find);
    int find_nw = d.find(find);

    //unite deque
    if(find_nw == pr_find) {
      while(!ord[find].empty()) {
        ord[pr_find].push_back(ord[find].front());
        ord[find].pop_front();
      }
    }
    else {
      while(!ord[pr_find].empty()) {
        ord[find].push_front(ord[pr_find].back());
        ord[pr_find].pop_back();
      }
    }
    
    //unite 01
    dat[find_nw] = {val_nw, find_nw, zero_nw, one_nw, root_nw, siz_nw};

    q.push(dat[find_nw]);
    while(!q.empty() && q.top().siz != d.size(q.top().idx)) q.pop();
  }

  int leader = d.find(0);
  vector<int> ret;
  while(!ord[leader].empty()) {
    ret.emplace_back(ord[leader].front());
    ord[leader].pop_front();
  }
  return ret;
}