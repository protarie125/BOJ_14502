#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;

using ll = long long;
using vb = vector<bool>;
using vvb = vector<vb>;
using vi = vector<int>;
using vvi = vector<vi>;
using vl = vector<ll>;
using pii = pair<int, int>;
using vii = vector<pii>;
using qii = queue<pii>;

int n, m;
vvi f;
int ans;

const auto& dx = vi{ -1,1,0,0 };
const auto& dy = vi{ 0,0,-1,1 };

void bfs() {
	auto cp = vvi{ f };

	auto q = qii{};
	for (auto i = 0; i < n; ++i) {
		for (auto j = 0; j < m; ++j) {
			if (2 == cp[i][j]) {
				q.push({ i, j });
			}
		}
	}

	while (!q.empty()) {
		auto fr = q.front();
		q.pop();

		const auto& x = fr.second;
		const auto& y = fr.first;

		for (auto d = 0; d < 4; ++d) {
			const auto& nx = x + dx[d];
			const auto& ny = y + dy[d];

			if (nx < 0 || m <= nx ||
				ny < 0 || n <= ny) {
				continue;
			}

			if (0 != cp[ny][nx]) {
				continue;
			}

			cp[ny][nx] = 2;
			q.push({ ny, nx });
		}
	}

	auto ct = int{ 0 };
	for (auto i = 0; i < n; ++i) {
		for (auto j = 0; j < m; ++j) {
			if (0 == cp[i][j]) {
				++ct;
			}
		}
	}

	if (ans < ct) {
		ans = ct;
	}
}

void solve(int b) {
	if (3 == b) {
		bfs();
		return;
	}

	for (auto i = 0; i < n; ++i) {
		for (auto j = 0; j < m; ++j) {
			if (0 != f[i][j]) {
				continue;
			}

			f[i][j] = 1;
			solve(b + 1);
			f[i][j] = 0;
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	cin >> n >> m;
	f = vvi(n, vi(m, 0));
	for (auto i = 0; i < n; ++i) {
		for (auto j = 0; j < m; ++j) {
			cin >> f[i][j];
		}
	}

	ans = 0;
	solve(0);
	cout << ans;

	return 0;
}