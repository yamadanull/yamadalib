#pragma once

#include "orderedmap-base.hpp"

template <typename Key, typename Val, bool multi>
struct MapNode {
	using Ptr = typename RBSTBase<MapNode>::Ptr;
	Ptr l, r;
	Key key;
	Val val;
	int cnt;

	MapNode(const Key& k = Key(), const Val& v = Val())
		: l(), r(), key(k), val(v), cnt(1) {}
};

template <typename Key, typename Val>
struct Map : MapBase<MapNode<Key, Val, false>, false> {
	using base = MapBase<MapNode<Key, Val, false>, false>;

	Map() : base() {}

	Val& operator[](const Key& key) { return base::insert_key(key)->val; };
};

/**
 * @brief Ordered Map(順序付き連想配列)
 */
