#include<iostream>
#include<vector>
#include<queue>
#include<set>

using namespace std;

int N, M, D;
vector<vector<int>> board(15, vector<int>(15));
vector<vector<int>> cpy(15, vector<int>(15));
vector<int> person(3, -1);
int line;//성 열 위치
int ans = 0;

int dr[3] = {0, -1, 0};
int dc[3] = {-1, 0, 1};

void input() {
	cin >> N >> M >> D;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> board[i][j];
		}
	}
}

bool in_range(int r, int c) {
	return 0 <= r && r < line && 0 <= c && c < M;
}

struct point {
	int r;
	int c;
	int d;
};

//표적 찾고 제거 BFS
int attack() {
	set<pair<int, int>> s;
	for (int i = 0; i < 3; i++) {
		queue<point> q;
		int visit[15][15] = { 0, };

		q.push({ line - 1, person[i], 1 });
		visit[line - 1][person[i]] = 1;

		while (!q.empty()) {
			int r = q.front().r;
			int c = q.front().c;
			int d = q.front().d;
			q.pop();
			if (cpy[r][c] == 1) {
				if (s.find({ r, c }) == s.end()) {
					s.insert({ r, c });
				}
				break;
			}

			if (d == D) {
				continue;
			}

			for (int i = 0; i < 3; i++) {
				if (!in_range(r + dr[i], c + dc[i])
					|| visit[r + dr[i]][c + dc[i]] > 0) {
					continue;
				}

				q.push({ r + dr[i], c + dc[i], d + 1 });
				visit[r + dr[i]][c + dc[i]] = d + 1;
			}
		}
	}

	for (auto temp : s) {
		cpy[temp.first][temp.second] = 0;
	}
	return (int)s.size();
}

void play() {
	line = N;//성 위치
	cpy = board;
	int score = 0;
	while (line > 0) {
		score += attack();
		line--;
	}
	if (ans < score) {
		ans = score;
	}
	//cout << score << "\n";
}

// 궁수 위치 Combination
void select_posision(int idx, int n) {
	if (n == 3) {
		//cout << person[0] << person[1] << person[2] << " :  ";
		play();
		//cout << "--------------------------------" << endl;
		return;
	}

	for (int i = idx; i < M; i++) {
		person[n] = i;
		select_posision(i + 1, n + 1);
	}
}

int main() {
	input();
	select_posision(0, 0);
	cout << ans;
	return 0;
}
