#include<iostream>
#include<vector>

using namespace std;

int M, S;
int sx, sy;
vector<int> board[5][5];
vector<int> cpy_board[5][5];
int smell[5][5];

void pb() {
	cout << "----------- print board ----------------" << endl;
	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 4; j++) {
			cout << board[i][j].size() << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void ps() {
	cout << "----------- print smell ----------------" << endl;
	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 4; j++) {
			cout << smell[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

//물고기 복사
void fish_copy() {
	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 4; j++) {
			cpy_board[i][j] = board[i][j];
		}
	}
}

int fdr[8] = { 1,0,-1,-1,-1,0,1,1 };
int fdc[8] = { -1,-1,-1,0,1,1,1,0 };
void fish_move() {
	vector<int> temp[5][5];
	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 4; j++) {
			for (int f = 0; f < board[i][j].size(); f++) {
				int nd = board[i][j][f];
				for (int d = 0; d < 8; d++) {
					int nr = i + fdr[(nd + 8 - d) % 8];
					int nc = j + fdc[(nd + 8 - d) % 8];
					if (nr < 1 || nr>4 || nc < 1 || nc>4
						|| smell[nr][nc] > 0
						|| (sx == nr && sy == nc)) {

						if (d == 7) {
							temp[i][j].push_back(nd);
						}
						continue;
					}

					temp[nr][nc].push_back((nd + 8 - d) % 8);
					break;
				}
			}
		}
	}

	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 4; j++) {
			board[i][j] = temp[i][j];
		}
	}
}

int max_fish = -1;
int sdr[4] = { -1,0,1,0 };
int sdc[4] = { 0,-1,0,1 };
vector<pair<int,int>> path;
vector<pair<int,int>> max_path;
int visit[5][5];
void shark_move(int cnt, int fish, int nr, int nc) {//상어 이동 경로(DFS)
	if (cnt == 3) {
		if (max_fish < fish) {
			max_fish = fish;
			max_path = path;
		}
		return;
	}

	for (int i = 0; i < 4; i++) {
		if (nr + sdr[i] < 1 || nr + sdr[i]>4 || nc + sdc[i] < 1 || nc + sdc[i]>4) {
			continue;
		}

		path.push_back({ nr + sdr[i], nc + sdc[i] });
		if (visit[nr + sdr[i]][nc + sdc[i]] == 0) {
			visit[nr + sdr[i]][nc + sdc[i]] = 1;
			shark_move(cnt + 1, fish + board[nr + sdr[i]][nc + sdc[i]].size(), nr + sdr[i], nc + sdc[i]);
			visit[nr + sdr[i]][nc + sdc[i]] = 0;
		}
		else {
			shark_move(cnt + 1, fish, nr + sdr[i], nc + sdc[i]);
		}
		
		path.pop_back();
	}
}

void shark_eat() {//상어 경로 및 냄새 표시
	max_fish = -1;
	path.clear();
	max_path.clear();
	shark_move(0, 0, sx, sy);

	sx = max_path[2].first, sy = max_path[2].second;

	for (int i = 0; i < 3; i++) {
		if (board[max_path[i].first][max_path[i].second].size() > 0) {
			board[max_path[i].first][max_path[i].second].clear();
			smell[max_path[i].first][max_path[i].second] = 3;
		}
	}
}

void smell_count() {//냄새 제거
	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 4; j++) {
			if (smell[i][j] > 0) {
				smell[i][j]--;
			}
		}
	}
}

void fish_plus() {//복제 마법 완료
	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 4; j++) {
			if (cpy_board[i][j].size() > 0) {
				board[i][j].insert(board[i][j].end(), cpy_board[i][j].begin(), cpy_board[i][j].end());
			}
		}
	}
}

void magic() {
	fish_copy();
	//pb();
	fish_move();
	//pb();
	//cout << "--------- shark -------------" << endl << sx << " " << sy << endl;
	shark_eat();
	//pb();
	//cout << "--------- shark -------------" << endl << sx << " " << sy << endl;
	//ps();
	smell_count();
	//ps();
	fish_plus();
	//pb();
}

int main() {
	int fx, fy, d;
	cin >> M >> S;
	for (int i = 0; i < M; i++) {
		cin >> fx >> fy >> d;
		if (d == 8) {
			d = 0;
		}
		board[fx][fy].push_back(d);
	}
	cin >> sx >> sy;

	for (int i = 0; i < S; i++) {
		magic();
	}

	int ans = 0;
	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 4; j++) {
			if (board[i][j].size() > 0) {
				ans += board[i][j].size();
			}
		}
	}
	cout << ans;
	return 0;
}
