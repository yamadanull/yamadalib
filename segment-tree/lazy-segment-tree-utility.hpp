#pragma once

#include "../monoid/add-max.hpp"
#include "../monoid/add-min.hpp"
#include "../monoid/add-sum.hpp"
#include "../monoid/update-max.hpp"
#include "../monoid/update-min.hpp"
#include "../monoid/update-sum.hpp"
#include "segment-tree.hpp"
#include "lazy-segment-tree.hpp"

template <typename T>
using sum_segtree = SegmentTree<MONOID::Add<T>>;
template <typename T>
using min_segtree = SegmentTree<MONOID::Min<T>>;
template <typename T>
using max_segtree = SegmentTree<MONOID::Max<T>>;

template <typename T>
using addmax_lazyseg = LazySegmentTree<ACTED_MONOID::Add_Max<T>>;
template <typename T>
using addmin_lazyseg = LazySegmentTree<ACTED_MONOID::Add_Min<T>>;
template <typename T>
using addsum_lazyseg = LazySegmentTree<ACTED_MONOID::Add_Sum<T>>;
template <typename T>
using updatemax_lazyseg = LazySegmentTree<ACTED_MONOID::Update_Max<T>>;
template <typename T>
using updatemin_lazyseg = LazySegmentTree<ACTED_MONOID::Update_Min<T>>;
template <typename T>
using updatesum_lazyseg = LazySegmentTree<ACTED_MONOID::Update_Sum<T>>;

