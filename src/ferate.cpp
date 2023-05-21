#include <bits/stdc++.h>

using namespace std;

class Task {
public:
	void solve() {
		read_input();
		get_result();
		print_output();
	}

private:
	// Initial graph
	vector<vector<int32_t>> graph;
	// Which SSC a node is part of
	vector<int32_t> component;
	// 
	vector<bool> visited_component;

	vector<bool> visited_node;

	int32_t n, m, source;
	int32_t result = 0;

	// Used for discovering SSCs
	vector<vector<int32_t>> ctc;
	vector<int32_t> found;
	vector<int32_t> low_link;
	vector<int32_t> in_stack;
	stack<int32_t> st;

	void read_input() {
		cin >> n >> m >> source;

		graph = vector<vector<int32_t>>(n + 1, vector<int32_t>());
		in_stack = vector<int32_t>(n + 1, 0);
		found = vector<int32_t>(n + 1, -1);
		low_link = vector<int32_t>(n + 1, 0);
		component = vector<int32_t>(n + 1, -1);
		visited_node = vector<bool>(n + 1, false);

		int32_t x, y;
		for (int32_t i = 0; i < m; i++) {
			cin >> x >> y;

			graph[x].push_back(y);
		}
	}

	void get_result() {
		int32_t current_start = 0;
		tarjan(source, current_start);
		for (int32_t i = 1; i <= n; i++) {
			if (found[i] == -1) {
				tarjan(i, current_start);
			}
		}

		result = ctc.size() - 1;
		visited_component = vector<bool>(ctc.size(), false);
		visited_component[component[source]] = true;
		for (int32_t i = 1; i <= n; i++) {
			if (!visited_node[i])
				dfs(i);
		}
	}

	void tarjan(int32_t node, int32_t &current_start) {
		found[node] = current_start;
		low_link[node] = current_start;

		in_stack[node] = 1;
		st.push(node);

		current_start = current_start + 1;

		for (auto neighbour : graph[node]) {
			if (found[neighbour] == -1) {
				tarjan(neighbour, current_start);
				low_link[node] = min(low_link[node], low_link[neighbour]);
			} else {
				if (in_stack[neighbour] == 1) {
					low_link[node] = min(low_link[node], found[neighbour]);
				}
			}
		}

		if (low_link[node] == found[node]) {
			int32_t current = -1;
			vector<int32_t> new_ctc;

			while (!st.empty() && current != node) {
				current = st.top();
				st.pop();
				new_ctc.push_back(current);

				component[current] = ctc.size();
				in_stack[current] = 0;
			}
			ctc.push_back(new_ctc);
		}
	}

	void dfs(int32_t node) {
		visited_node[node] = true;
		for (auto neigh : graph[node]) {
			if (component[node] != component[neigh]
				&& !visited_component[component[neigh]]) {
				result--;
				visited_component[component[neigh]] = true;
			}
			if (!visited_node[node])
				dfs(neigh);
		}
	}

	void print_output() {
		cout << result << "\n";
	}
};

int main() {
	std::ios::sync_with_stdio(false);
	freopen("ferate.in", "r", stdin);
	freopen("ferate.out", "w", stdout);
	cin.tie(NULL);
	cout.tie(NULL);

	auto *task = new (nothrow) Task();
	if (!task) {
		cerr << "new failed: WTF are you doing? Throw your PC!\n";
		return -1;
	}

	task->solve();
	delete task;
	return 0;
}
