#pragma once
// F: query info
template <typename F>
struct SegmentTreeDandC {
	int Q, width;
	vector<vector<F>> seg;

	SegmentTreeDandC(int _Q) : Q(_Q) {
		width = 1;
		while (width < Q) width *= 2;
		seg.resize(width * 2);
	}

	void apply(int l, int r, F q) {
		l += width;
		r += width;
		while (l < r) {
			if (l & 1) seg[l++].emplace_back(q);
			if (r & 1) seg[--r].emplace_back(q);
			l >>= 1, r >>= 1;
		}
	}

	vector<F> operator[](int k) { return seg[k]; }

	template <typename T0, typename T1, typename T2, typename T3>
	void run(T0 marge, T1 get_time, T2 rollback, T3 query) {
		auto dfs = [&](auto&& dfs, int l, int r, int u)->void{
			if (l >= Q) return;
			int time = get_time();
			for (auto& f : seg[u]) marge(f);
			if (r - l == 1) query(u - width);
			else {
				dfs(dfs, l, (l + r) / 2, u * 2 + 0);
				dfs(dfs, (l + r) / 2, r, u * 2 + 1);
			}
			rollback(time);
		};
		dfs(dfs, 0, width, 1);
	}
};

// template to use "run"
/*
	using F = ;
	SegmentTreeDandC<F> seg(Q);

	// (calc query range, declarate info, exc...)

	auto marge = [&](F q)->void{
	};
	auto get_time = [&]()->int{
	};
	auto rollback = [&](int time)->void{
	};
	auto query = [&](int qi)->void{
	};
	seg.run(marge, get_time, rollback, query);
*/
