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
	uint32_t n, q;
	vector<vector<uint32_t>> tree;
	vector<uint32_t> disc_times;
	vector<uint32_t> disc_times_inverted;
	vector<uint32_t> finish_times;

	uint32_t disc_time = 0, finish_time = 0;

	void read_input() {
		freopen("magazin.in", "r", stdin);
		freopen("magazin.out", "w", stdout);
		cin.tie(NULL);
		cout.tie(NULL);

		cin >> n >> q;
		tree = vector<vector<uint32_t>>(n + 1, vector<uint32_t>());
		disc_times = vector<uint32_t>(n + 1);
		finish_times = vector<uint32_t>(n + 1);
		disc_times_inverted = vector<uint32_t>(n);

		for (uint32_t i = 2; i <= n; i++) {
			uint32_t parent;
			cin >> parent;
			tree[parent].push_back(i);
		}
	}

	void get_result() {
		do_dfs(1);

		uint32_t start_node, dfs_steps;
		for (uint32_t i = 0; i < q; i++) {
			cin >> start_node >> dfs_steps;

			uint32_t child_disc_time = disc_times[start_node] + dfs_steps;

			if (child_disc_time < n) {
				uint32_t child = disc_times_inverted[child_disc_time];
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

	auto *task = new (nothrow) Task();
	if (!task) {
		cerr << "new failed: WTF are you doing? Throw your PC!\n";
		return -1;
	}
	task->solve();
	delete task;
	return 0;
}
