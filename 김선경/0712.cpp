#include <bits/stdc++.h>
using namespace std;

int _map[50][50];
int _diffuse[50][50];
vector<pair<int, int>> dust;
int upAir, downAir;
int r, c, t;

int dx[4] = { 0, 0, -1, 1 };
int dy[4] = { -1, 1, 0, 0 };

void diffuse() {
	int cnt = dust.size();

	for (int i = 0; i < cnt; i++) {
		int x = dust[i].first;
		int y = dust[i].second;

		int dSize = _map[x][y];

		int dCnt = 0;

		for (int d = 0; d < 4; d++) {
			int nx = x + dx[d];
			int ny = y + dy[d];
			

			if (nx < 0 || nx >= r || ny < 0 || ny >= c) {
				continue;
			}
			if (_map[nx][ny] == -1) {
				continue;
			}
			
			_diffuse[nx][ny] += dSize/5;
			dust.push_back({ nx, ny });
			dCnt++;
		}
		_diffuse[x][y] += dSize - (dSize / 5) * dCnt;
	}
}

void airOp() {
	//바람에 따른 이동
	int originDust;

	//1열 바람
	for (int i = upAir-2; i >= 0; i--) {
		originDust = _map[i][0];
		_map[i + 1][0] = originDust;
	}
	for (int i = downAir + 2; i < r; i++) {
		originDust = _map[i][0];
		_map[i - 1][0] = originDust;
	}

	//왼쪽으로 가는 바람
	for (int i = 1; i < c; i++) {
		originDust = _map[0][i];
		_map[0][i-1] = originDust;
		originDust = _map[r-1][i];
		_map[r-1][i - 1] = originDust;
	}

	//마지막열 바람
	for (int i = 1; i <= upAir; i++) {
		originDust = _map[i][c-1];
		_map[i-1][c-1] = originDust;
	}
	for (int i = r - 2; i >= downAir; i--) {
		originDust = _map[i][c-1];
		_map[i + 1][c-1] = originDust;
	}

	//오른쪽 바람
	for (int i = c - 2; i > 0; i--) {
		originDust = _map[upAir][i];
		_map[upAir][i + 1] = originDust;
		originDust = _map[downAir][i];
		_map[downAir][i + 1] = originDust;
	}

	_map[upAir][1] = 0;
	_map[downAir][1] = 0;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int totalDust=0;

	cin >> r >> c >> t;

	bool  air = false;

	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			cin >> _map[i][j];
			if (_map[i][j] == -1) {
				if (!air) {
					upAir = i;
					air = true;
				}
				else {
					downAir = i;
				}
			}
			else if (_map[i][j] > 0) {
				dust.push_back({ i, j });
			}
		}
	}


	while (t--) {
		_diffuse[upAir][0] = -1;
		_diffuse[downAir][0] = -1;

		diffuse();
		copy(&_diffuse[0][0], &_diffuse[0][0] + 50 * 50, &_map[0][0]);
		memset(_diffuse, 0, sizeof(_diffuse));
		airOp();

		dust.clear();
		for (int i = 0; i < r; i++) {
			for (int j = 0; j < c; j++) {
				if (_map[i][j] > 0)
					dust.push_back({ i, j });
			}
		}
	}

	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (_map[i][j] > 0)
				totalDust += _map[i][j];
		}
	}

	cout << totalDust;

	return 0;
}