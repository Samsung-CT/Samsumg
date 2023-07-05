#include <bits/stdc++.h>
using namespace std;

int N, M, K;
int nowMap[10][10]; //양분
//vector <pair<pair<int, int>, int>> v;//나무 나이 어린 친구부터 앞으로 가게 <<x,y>,z>
//위에 처럼 나무를 저장하면 전체 모든 map의 나무를 정령해야하므로,
//그 칸에 존재하는 나무들끼리만 정렬하게 하기
vector<int> treeInOne[10][10];

vector <pair<pair<int, int>, int>> deathTree; //죽은 나무 정보 모음
int addSize[10][10];

void spring() {
	//각 칸에 속한 나무들 정렬(어린나무순)
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			sort(treeInOne[i][j].begin(), treeInOne[i][j].end());
		}
	}
	
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int eraseCnt = 0;
			int vSize = treeInOne[i][j].size();
			for (int k = 0; k < vSize; k++) {
				//나이보다 양분이 많은 경우
				if (treeInOne[i][j][k -eraseCnt] <= nowMap[i][j]) {
					//양분 줄이고, 나이 늘림
					nowMap[i][j] -= treeInOne[i][j][k - eraseCnt];
					treeInOne[i][j][k - eraseCnt]++;
				}
				//양분이 적은 경우
				else {
					//죽은 나무에 추가
					//칸에 속한 나무에서 제거
					deathTree.push_back({ {i, j}, treeInOne[i][j][k - eraseCnt]});
					treeInOne[i][j].erase(treeInOne[i][j].begin() + k - eraseCnt);
					eraseCnt++;
				}
			}
		}
	}
}

void summer() {
	//죽은 나무의 나이의 절반을 양분으로 추가
	for (auto i : deathTree) {
		int x = i.first.first;
		int y = i.first.second;
		int age = i.second;

		nowMap[x][y] += (age / 2);
	}

	deathTree.clear();
}

int dx[8] = { -1,-1,-1,0,0,1,1,1 };
int dy[8] = { -1,0,1,-1,1,-1,0,1 };
void fall() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int vSize = treeInOne[i][j].size();
			for (int k = 0; k < vSize; k++) {
				//나이가 5의 배수이면
				//주변에 1살 나무 추가
				if (treeInOne[i][j][k] % 5 == 0) {
					for (int d = 0; d < 8; d++) {
						int nx = i + dx[d];
						int ny = j + dy[d];

						if (nx < 0 || nx >= N || ny < 0 || ny >= N)
							continue;

						treeInOne[nx][ny].push_back(1);
					}
				}
			}
		}
	}
}

void winter() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			//S2D2가 양분 추가
			nowMap[i][j] += addSize[i][j];
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin >> N >> M >> K;

	fill(nowMap[0], nowMap[10], 5);

	//각칸에 추가되는 양분 입력
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> addSize[i][j];
		}
	}

	//나무 정보 입력
	int x, y, z;
	for (int i = 0; i < M; i++) {
		cin >> x >> y >> z;
		treeInOne[x - 1][y - 1].push_back(z);
	}

	//K년동안 봄, 여름, 가을, 겨울 진행
	while (K--) {
		spring();
		summer();
		fall();
		winter();
	}

	int totalTreeCnt = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			totalTreeCnt += treeInOne[i][j].size();
		}
	}

	cout << totalTreeCnt;

	return 0;
}