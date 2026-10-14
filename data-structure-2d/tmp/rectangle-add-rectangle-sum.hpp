#pragma once

#include "../data-structure/binary-indexed-tree.hpp"
#include <algorithm>

template <typename I, typename T>
struct RectangleAddRectangleSum {
	struct AddQuery { I xl, xr, yl, yr; T val; };
	struct SumQuery { I xl, xr, yl, yr; };
	std::vector<AddQuery> add_qs;
	std::vector<SumQuery> sum_qs;

	public:
	RectangleAddRectangleSum() = default;

	void add_rectangle(I xl, I xr, I yl, I yr, T val) {
		add_qs.emplace_back(AddQuery{xl, xr, yl, yr, val});
	}
	void add_query(I xl, I xr, I yl, I yr) {
		sum_qs.emplace_back(SumQuery{xl, xr, yl, yr});
	}

	std::vector<T> solve() const {
		std::vector<I> ys;
		for (const auto &a : add_qs) {
			ys.emplace_back(a.yl);
			ys.emplace_back(a.yr);
		}
		std::ranges::sort(ys);
		ys.erase(std::ranges::unique(ys).begin(), ys.end());

		const int Y = ys.size();

		std::vector<std::tuple<I, int, int>> ops;
		for (int qi = 0; qi < int(sum_qs.size()); ++qi) {
			ops.emplace_back(sum_qs[qi].xl, 0, qi);
			ops.emplace_back(sum_qs[qi].xr, 1, qi);
		}
		for (int qi = 0; qi < int(add_qs.size()); ++qi) {
			ops.emplace_back(add_qs[qi].xl, 2, qi);
			ops.emplace_back(add_qs[qi].xr, 3, qi);
		}
		std::ranges::sort(ops);

		BinaryIndexedTree<T> b00(Y), b01(Y), b10(Y), b11(Y);
		std::vector<T> ret(sum_qs.size());
		for (auto o : ops) {
			int qtype = get<1>(o), qi = get<2>(o);
			if (qtype >= 2) {
				const AddQuery &q = add_qs.at(qi);
				int i = lower_bound(ys.begin(), ys.end(), q.yl) - ys.begin();
				int j = lower_bound(ys.begin(), ys.end(), q.yr) - ys.begin();
				T x = get<0>(o);
				T yi = q.yl, yj = q.yr;
				if (qtype & 1) std::swap(i, j), std::swap(yi, yj);

				b00.add(i, x * yi * q.val);
				b01.add(i, -x * q.val);
				b10.add(i, -yi * q.val);
				b11.add(i, q.val);
				b00.add(j, -x * yj * q.val);
				b01.add(j, x * q.val);
				b10.add(j, yj * q.val);
				b11.add(j, -q.val);
			}
			else {
				const SumQuery &q = sum_qs.at(qi);
				int i = std::ranges::lower_bound(ys, q.yl) - ys.begin();
				int j = std::ranges::lower_bound(ys, q.yr) - ys.begin();
				T x = get<0>(o);
				T yi = q.yl, yj = q.yr;
				if (qtype & 1) std::swap(i, j), std::swap(yi, yj);

				i--, j--;
				ret[qi] += b00.sum(i) + b01.sum(i) * yi + b10.sum(i) * x + b11.sum(i) * x * yi;
				ret[qi] -= b00.sum(j) + b01.sum(j) * yj + b10.sum(j) * x + b11.sum(j) * x * yj;
			}
		}
		return ret;
	}
};
