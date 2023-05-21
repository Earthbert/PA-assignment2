#include <bits/stdc++.h>
using namespace std;

class Task {
	public:
	void solve() {
		read_input();
		print_output(get_result());
	}

	private:
	uint32_t nr_nodes, nr_deps;
	// Which data set a task is using
	vector<uint32_t> data_sets;
	// Dependecies between tasks
	vector<vector<uint32_t>> deps;
	// In_degree of the task nodes used for Kahn
	vector<uint32_t> in_degree;

	void read_input() {
		cin >> nr_nodes >> nr_deps;
		data_sets = vector<uint32_t>(nr_nodes + 1);
		deps = vector<vector<uint32_t>>(nr_nodes + 1, vector<uint32_t>());
		in_degree = vector<uint32_t>(nr_nodes + 1, 0);

		for (uint32_t i = 1; i <= nr_nodes; i++) {
			cin >> data_sets[i];
		}

		for (uint32_t i = 0; i < nr_deps; i++) {
			uint32_t u, v;
			cin >> u >> v;
			deps[u].push_back(v);
			in_degree[v]++;
		}
	}

	uint32_t get_result() {
		// Queue for tasks that use dataset 1
		queue<uint32_t> q_1;
		// Queue for tasks that use dataset 1
		queue<uint32_t> q_2;

		for (uint32_t i = 1; i <= nr_nodes; i++) {
			if (in_degree[i] == 0) {
				if (data_sets[i] == 1) {
					q_1.push(i);
				} else {
					q_2.push(i);
				}
			}
		}

		uint32_t context_switches = min(try_kahn(1, q_1, q_2, in_degree),
			try_kahn(2, q_1, q_2, in_degree));

		return context_switches;
	}


	/**
	 * @brief Uses Kahn algorithm to perform a topological sort
	 * @param start_data_set Which data set to start with
	 * @param q_1 Queue of task that use dataset 1
	 * @param q_2 Queue of task that use dataset 1
	 * @param in_degree Indegree of nodes
	 * @return Number of context switches needed
	 */
	uint32_t try_kahn(uint32_t start_data_set,
		queue<uint32_t>q_1,
		queue<uint32_t>q_2,
		vector<uint32_t> in_degree) {
		if (start_data_set == 1 && q_1.empty())
			return INT32_MAX;
		if (start_data_set == 2 && q_2.empty())
			return INT32_MAX;

		uint8_t current_data_set = start_data_set;
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
			}

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
		cout << result << "\n";
	}
};

int main() {
	std::ios::sync_with_stdio(false);
	freopen("supercomputer.in", "r", stdin);
	freopen("supercomputer.out", "w", stdout);
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
