#include <bits/stdc++.h>
#include <sys/time.h>
using namespace std;

class Task {
	public:
	void solve() {
		read_input();
		get_result();
	}

	private:
	uint32_t nr_nodes, nr_questions;
	// Tree used for dfs
	vector<vector<uint32_t>> tree;
	// Time a node was discovered
	vector<uint32_t> disc_times;
	// Which node was discovered at a specific time
	vector<uint32_t> disc_times_inverted;
	// Time a node was finished
	vector<uint32_t> finish_times;

	uint32_t disc_time = 0, finish_time = 0;

	void read_input() {
		cin >> nr_nodes >> nr_questions;
		tree = vector<vector<uint32_t>>(nr_nodes + 1, vector<uint32_t>());
		disc_times = vector<uint32_t>(nr_nodes + 1);
		finish_times = vector<uint32_t>(nr_nodes + 1);
		disc_times_inverted = vector<uint32_t>(nr_nodes);

		for (uint32_t i = 2; i <= nr_nodes; i++) {
			uint32_t parent;
			cin >> parent;
			tree[parent].push_back(i);
		}
	}

	void get_result() {
		do_dfs(1);

		uint32_t start_node, dfs_steps;
		for (uint32_t i = 0; i < nr_questions; i++) {
			cin >> start_node >> dfs_steps;

			// Child discovery time if after dfs_steps
			uint32_t child_disc_time = disc_times[start_node] + dfs_steps;

			// Check if time is valid
			if (child_disc_time < nr_nodes) {
				uint32_t child = disc_times_inverted[child_disc_time];
				// Check if child is in the same subtree as start_node
				if (finish_times[child] < finish_times[start_node]) {
					cout << child << "\n";
					continue;
				}
			}
			cout << -1 << "\n";
		}
	}

	void do_dfs(uint32_t current_node) {
		disc_times[current_node] = disc_time;
		disc_times_inverted[disc_time] = current_node;
		disc_time++;

		for (auto child : tree[current_node])
			do_dfs(child);

		finish_times[current_node] = finish_time;
		finish_time++;
	}
};

int main() {
	std::ios::sync_with_stdio(false);
	freopen("magazin.in", "r", stdin);
	freopen("magazin.out", "w", stdout);
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
