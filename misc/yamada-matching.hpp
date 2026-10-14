#pragma once

template <typename T>
std::vector<std::pair<int, int>> yamadaMatching(std::vector<T> &A){
	int N = A.size();
	std::priority_queue<std::pair<T, int>> q;
	for (int i = 0; i < N; i++) if (A[i] >= 1) q.emplace(A[i], i);
	std::vector<std::pair<int, int>> ans;
	while (q.size() >= 2) {
		auto [a, i] = q.top(); q.pop();
		auto [b, j] = q.top(); q.pop();
		ans.emplace_back(i, j);
		if (a >= 2) q.emplace(a - 1, i);
		if (b >= 2) q.emplace(b - 1, j);
	}
	return ans;
}

