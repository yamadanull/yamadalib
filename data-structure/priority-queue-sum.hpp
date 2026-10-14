#pragma once

template <typename G, bool Minimize = true>
struct PriorityQueueSum {
	using Queue =
		conditional_t<Minimize, priority_queue<G, vector<G>, greater<G>>,
		priority_queue<G>>;
	Queue Q, Q2;
	G sum;

	PriorityQueueSum(G ti) : sum(ti) {}
	PriorityQueueSum() : sum(G()) {}

	void push(const G& t) {
		Q.push(t);
		sum += t;
	}

	G top() {
		normalize();
		assert(!Q.empty());
		return Q.top();
	}

	G pop() {
		normalize();
		assert(!Q.empty());
		G ans = Q.top();
		Q.pop();
		sum -= ans;
		return ans;
	}
	void erase(const G& t) {
		Q2.push(t);
		sum -= t;
	}

	int size() { return (int)Q.size() - (int)Q2.size(); }
	bool empty() { return size() == 0; }

	private:
	void normalize() {
		while (!Q.empty() and !Q2.empty() and Q.top() == Q2.top()) {
			Q.pop(), Q2.pop();
		}
	}
};
