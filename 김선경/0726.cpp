#include <bits/stdc++.h>
using namespace std;

int n, m, energy;

vector<pair<int, int>> start;
vector<pair<int, int>> dest;
int driveX, driveY;

int _map[21][21];
bool visited[21][21];
int dx[4] = { -1, 1,  0, 0 };
int dy[4] = { 0, 0,-1, 1 };
bool noReach;

int bfs(int sx, int sy, int dex, int dey) {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			visited[i][j] = false;
		}
	}


	queue <pair<pair<int, int>, int>> q;
	q.push({ { sx, sy }, 0 });
	visited[sx][sy] = true;

	while (!q.empty()) {
		int x = q.front().first.first;
		int y = q.front().first.second;
		int dist = q.front().second;
		q.pop();

		if (x == dex && y == dey)
			return dist;
		
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];

			if (nx <= 0 || nx > n || ny <= 0 || ny > n) continue;
			if (visited[nx][ny]) continue;
			if (_map[nx][ny] == 1) continue;

			q.push({ {nx, ny}, dist + 1 });
			visited[nx][ny] = true;
		}
	}

	noReach = true;
	return -1;
}

pair<int, int> pick() {
	int minDis = 999999, minIdx = 0;
	for (int i = 0; i < start.size(); i++) {
		int dist = bfs(start[i].first, start[i].second, driveX, driveY);
		
		if (minDis > dist) {
			minDis = dist;
			minIdx = i;
		}
		else if (minDis == dist) {
			if (start[minIdx].first > start[i].first) {
				minIdx = i;
			}
			else if (start[minIdx].first == start[i].first) {
				if (start[minIdx].second > start[i].second)
					minIdx = i;
			}
		}
	}

	return { minIdx, minDis };
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin >> n >> m >> energy;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> _map[i][j];
		}
	}

	cin >> driveX >> driveY;

	int sx, sy, dx, dy;
	for (int i = 0; i < m; i++) {
		cin >> sx >> sy >> dx >> dy;
		start.push_back({ sx, sy });
		dest.push_back({ dx, dy });
	}

	while (!start.empty()) {
		//택시에서 가장 가까운 손님 위치 찾기
		pair<int, int> near;
		near = pick();
		int idx = near.first;
		energy -= near.second;

		//그 손님의 목적지 데려다 주기
		//이때, 연료가 떨어지면 energy -1로 바꾸고 break
		int dist = bfs(start[idx].first, start[idx].second, dest[idx].first, dest[idx].second);
		if ((energy - dist) < 0) {
			cout << -1;
			return 0;
		}
		else {
			energy += dist;
			driveX = dest[idx].first;
			driveY = dest[idx].second;
			start.erase(start.begin() + idx);
			dest.erase(dest.begin() + idx);
		}

		if (noReach) {
			cout << -1;
			return 0;
		}
	}

	cout << energy;

	return 0;
}