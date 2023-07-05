#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int N, M, K; // N : 상도땅크기 , M : 나무의 개수 , K : 년
int A[11][11];
int energy[11][11];
vector<int> trees[11][11];
int dy[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dx[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

bool inRange(int y, int x) {
    if (y >= 1 && x >= 1 && y <= N && x <= N)
        return true;

    return false;
}

void Debugg() {
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cout << energy[i][j] << " ";
        }
        cout << '\n';
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (!trees[i][j].empty()) {
                for (int k = 0; k < trees[i][j].size(); k++) {
                    cout << trees[i][j][k] << " ";
                }
            }
        }
        cout << '\n';
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cout << trees[i][j].size() << " ";
        }
        cout << '\n';
    }
    cout << '\n';
}

// 봄에는 나무가 자신의 나이만큼 양분을 먹고, 나이가 1 증가한다.
// 하나의 칸에 여러 개의 나무가 있다면 나이가 어린 나무부터 양분을 먹고, 양분이 부족해 자신의 나이만큼 양분을 먹을수 없는 나무는 양분을 먹지 못하고 죽는다.
// 여름에는 죽은 나무가 양분으로 다시 변한다. 죽은 나무마다 나이를 2로 나눈 값이 나무가 있던 칸에 양분으로 추가된다.
void SpringSummer() {
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (!trees[i][j].empty()) {                       // 나무가 있다면
                sort(trees[i][j].begin(), trees[i][j].end()); // 정렬 후
                vector<int> temp;
                int dead_trees = 0;
                for (int k = 0; k < trees[i][j].size(); k++) {
                    if (trees[i][j][k] <= energy[i][j]) {
                        energy[i][j] -= trees[i][j][k];
                        temp.push_back(trees[i][j][k] + 1);
                    } else {
                        dead_trees += trees[i][j][k] / 2;
                    }
                }
                energy[i][j] += dead_trees;
                trees[i][j].clear();
                for (int k = 0; k < temp.size(); k++) {
                    trees[i][j].push_back(temp[k]);
                }
            }
        }
    }
}

void Fall() {
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (!trees[i][j].empty()) {
                for (int k = 0; k < trees[i][j].size(); k++) {
                    if (trees[i][j][k] % 5 == 0) {
                        for (int s = 0; s < 8; s++) {
                            int next_y = i + dy[s];
                            int next_x = j + dx[s];
                            if (inRange(next_y, next_x)) {
                                trees[next_y][next_x].push_back(1);
                            }
                        }
                    }
                }
            }
        }
    }
}

void Winter() {
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            energy[i][j] += A[i][j];
        }
    }
}

void Solve() {
    for (int i = 0; i < K; i++) {
        Debugg();
        cout << i + 1 << "년 후 \n";
        SpringSummer();
        Fall();
        Winter();
        // Debugg();
    }

    int result = 0;

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            result += trees[i][j].size();
        }
    }

    cout << result;
}

int main() {
    cin >> N >> M >> K;

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cin >> A[i][j];
        }
    }

    for (int i = 0; i < M; i++) {
        int y, x, age;
        cin >> y >> x;
        trees[y][x].push_back(age);
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            energy[i][j] = 5;
        }
    }

    Solve();

    return 0;
}