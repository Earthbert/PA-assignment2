#include <bits/stdc++.h>
using namespace std;

class Task {
public:
	void solve() {
		read_input();
		print_output(get_result());
	}

private:
	uint32_t n, m;
	vector<uint32_t> data_sets;
	vector<vector<uint32_t>> deps;
	vector<uint32_t> in_degree;

	void read_input() {
		freopen("supercomputer.in", "r", stdin);
		cin >> n >> m;
		data_sets = vector<uint32_t>(n + 1);
		deps = vector<vector<uint32_t>>(n + 1, vector<uint32_t>());
		in_degree = vector<uint32_t>(n + 1, 0);

		for (uint32_t i = 1; i <= n; i++) {
			cin >> data_sets[i];
		}

		for (uint32_t i = 0; i < m; i++) {
			uint32_t u, v;
			cin >> u >> v;
			deps[u].push_back(v);
			in_degree[v]++;
		}
	}

	uint32_t get_result() {
		queue<uint32_t> q_1;
		queue<uint32_t> q_2;
		vector<uint32_t> topsort;

		for (uint32_t i = 1; i <= n; i++) {
			if (in_degree[i] == 0) {
				if (data_sets[i] == 1) {
					q_1.push(i);
				} else {
					q_2.push(i);
				}
			}
		}

		uint8_t current_data_set = 0;
		uint32_t context_switches = 0;
		while (!q_1.empty() || !q_2.empty()) {
			uint32_t node;
			if (current_data_set == 1) {
				if (!q_1.empty()) {
					node = q_1.front();
					q_1.pop();
					current_data_set = 1;
				} else {
					node = q_2.front();
					q_2.pop();
					context_switches++;
					current_data_set = 2;
				}
			} else if (current_data_set == 2) {
				if (!q_2.empty()) {
					node = q_2.front();
					q_2.pop();
					current_data_set = 2;
				} else {
					node = q_1.front();
					q_1.pop();
					context_switches++;
					current_data_set = 1;
				}
			} else {
				if (!q_1.empty()) {
					node = q_1.front();
					q_1.pop();
					current_data_set = 1;
				} else {
					node = q_2.front();
					q_2.pop();
					current_data_set = 2;
				}
			}

			topsort.push_back(node);
			for (auto neigh : deps[node]) {
				in_degree[neigh]--;
				if (in_degree[neigh] == 0) {
					if (data_sets[neigh] == 1)
						q_1.push(neigh);
					else
						q_2.push(neigh);
				}
			}
		}

		return context_switches;
	}

	void print_output(uint32_t result) {
		freopen("supercomputer.out", "w", stdout);
		cout << result;
	}
};

int main() {
	std::ios::sync_with_stdio(false);
	auto *task = new (nothrow) Task();
	if (!task) {
		cerr << "new failed: WTF are you doing? Throw your PC!\n";
		return -1;
	}
	task->solve();
	delete task;
	return 0;
}
