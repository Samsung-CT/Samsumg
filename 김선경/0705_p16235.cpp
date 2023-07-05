#include <bits/stdc++.h>
using namespace std;

int N, M, K;
int nowMap[10][10]; //���
//vector <pair<pair<int, int>, int>> v;//���� ���� � ģ������ ������ ���� <<x,y>,z>
//���� ó�� ������ �����ϸ� ��ü ��� map�� ������ �����ؾ��ϹǷ�,
//�� ĭ�� �����ϴ� �����鳢���� �����ϰ� �ϱ�
vector<int> treeInOne[10][10];

vector <pair<pair<int, int>, int>> deathTree; //���� ���� ���� ����
int addSize[10][10];

void spring() {
	//�� ĭ�� ���� ������ ����(�������)
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
				//���̺��� ����� ���� ���
				if (treeInOne[i][j][k -eraseCnt] <= nowMap[i][j]) {
					//��� ���̰�, ���� �ø�
					nowMap[i][j] -= treeInOne[i][j][k - eraseCnt];
					treeInOne[i][j][k - eraseCnt]++;
				}
				//����� ���� ���
				else {
					//���� ������ �߰�
					//ĭ�� ���� �������� ����
					deathTree.push_back({ {i, j}, treeInOne[i][j][k - eraseCnt]});
					treeInOne[i][j].erase(treeInOne[i][j].begin() + k - eraseCnt);
					eraseCnt++;
				}
			}
		}
	}
}

void summer() {
	//���� ������ ������ ������ ������� �߰�
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
				//���̰� 5�� ����̸�
				//�ֺ��� 1�� ���� �߰�
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
			//S2D2�� ��� �߰�
			nowMap[i][j] += addSize[i][j];
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin >> N >> M >> K;

	fill(nowMap[0], nowMap[10], 5);

	//��ĭ�� �߰��Ǵ� ��� �Է�
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> addSize[i][j];
		}
	}

	//���� ���� �Է�
	int x, y, z;
	for (int i = 0; i < M; i++) {
		cin >> x >> y >> z;
		treeInOne[x - 1][y - 1].push_back(z);
	}

	//K�⵿�� ��, ����, ����, �ܿ� ����
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