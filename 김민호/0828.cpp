#include <algorithm>
#include <iostream>
using namespace std;
int N;
int map[21][21];
int result = 0;

void MoveUp(int, int[][21]);
void MoveDown(int, int[][21]);
void MoveLeft(int, int[][21]);
void MoveRight(int, int[][21]);

void Debugg(int temp_map[21][21]) {
    cout << '\n';
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << temp_map[i][j] << " ";
        }
        cout << '\n';
    }
}

int checkBiggestBlock(int copied_map[21][21]) {
    int max_block = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (copied_map[i][j] > max_block) {
                max_block = copied_map[i][j];
            }
        }
    }

    return max_block;
}

void MoveUp(int cnt, int copied_map[21][21]) {
    if (cnt == 5) {
        result = max(result, checkBiggestBlock(copied_map));
        return;
    }

    int temp_map[21][21];
    for (int i = 0; i < N; i++) { // 맵 복사
        for (int j = 0; j < N; j++) {
            temp_map[i][j] = copied_map[i][j];
        }
    }

    // 빈 칸 먼저 당김. 합치는건 아직 X
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N; j++) {
            bool flag = false;
            if (temp_map[i][j] == 0) {
                int k = i + 1;
                while (k <= N - 1) {
                    if (temp_map[k][j] != 0) {
                        flag = true;
                        break;
                    }
                    k++;
                }
                if (flag) {
                    temp_map[i][j] = temp_map[k][j];
                    temp_map[k][j] = 0;
                }
            }
        }
    }

    // 다음 아랫칸에 같은 크기 블록이 있으면 합친다
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N; j++) {
            if (temp_map[i][j] == temp_map[i + 1][j]) {
                temp_map[i][j] = temp_map[i][j] * 2;
                temp_map[i + 1][j] = 0;
            }
        }
    }

    // 합치고 나서 생긴 공백 메꾸기
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N; j++) {
            bool flag = false;
            if (temp_map[i][j] == 0) {
                int k = i + 1;
                while (k <= N - 1) {
                    if (temp_map[k][j] != 0) {
                        flag = true;
                        break;
                    }
                    k++;
                }
                if (flag) {
                    temp_map[i][j] = temp_map[k][j];
                    temp_map[k][j] = 0;
                }
            }
        }
    }

    // Debugg(temp_map);

    MoveUp(cnt + 1, temp_map);
    MoveDown(cnt + 1, temp_map);
    MoveLeft(cnt + 1, temp_map);
    MoveRight(cnt + 1, temp_map);
}

void MoveDown(int cnt, int copied_map[21][21]) {
    if (cnt == 5) {
        result = max(result, checkBiggestBlock(copied_map));
        return;
    }

    int temp_map[21][21];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            temp_map[i][j] = copied_map[i][j];
        }
    }

    // 빈 칸 먼저 당김. 합치는건 아직 X
    for (int i = N - 1; i > 0; i--) {
        for (int j = 0; j < N; j++) {
            bool flag = false;
            if (temp_map[i][j] == 0) {
                int k = i - 1;
                while (k >= 0) {
                    if (temp_map[k][j] != 0) {
                        flag = true;
                        break;
                    }
                    k--;
                }
                if (flag) {
                    temp_map[i][j] = temp_map[k][j];
                    temp_map[k][j] = 0;
                }
            }
        }
    }

    // 다음 아랫칸에 같은 크기 블록이 있으면 합친다
    for (int i = N - 1; i > 0; i--) {
        for (int j = 0; j < N; j++) {
            if (temp_map[i - 1][j] == temp_map[i][j]) {
                temp_map[i][j] = temp_map[i][j] * 2;
                temp_map[i - 1][j] = 0;
            }
        }
    }

    // 합치고 나서 생긴 공백 메꾸기
    for (int i = N - 1; i > 0; i--) {
        for (int j = 0; j < N; j++) {
            bool flag = false;
            if (temp_map[i][j] == 0) {
                int k = i - 1;
                while (k >= 0) {
                    if (temp_map[k][j] != 0) {
                        flag = true;
                        break;
                    }
                    k--;
                }
                if (flag) {
                    temp_map[i][j] = temp_map[k][j];
                    temp_map[k][j] = 0;
                }
            }
        }
    }

    MoveUp(cnt + 1, temp_map);
    MoveDown(cnt + 1, temp_map);
    MoveLeft(cnt + 1, temp_map);
    MoveRight(cnt + 1, temp_map);
}

void MoveRight(int cnt, int copied_map[21][21]) {
    if (cnt == 5) {
        result = max(result, checkBiggestBlock(copied_map));
        return;
    }

    int temp_map[21][21];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            temp_map[i][j] = copied_map[i][j];
        }
    }

    // 빈 칸 먼저 당김. 합치는건 아직 X
    for (int i = 0; i < N; i++) {
        for (int j = N - 1; j > 0; j--) {
            bool flag = false;
            if (temp_map[i][j] == 0) {
                int k = j - 1;
                while (k >= 0) {
                    if (temp_map[i][k] != 0) {
                        flag = true;
                        break;
                    }
                    k--;
                }
                if (flag) {
                    temp_map[i][j] = temp_map[i][k];
                    temp_map[i][k] = 0;
                }
            }
        }
    }

    // 다음 아랫칸에 같은 크기 블록이 있으면 합친다
    for (int i = 0; i < N; i++) {
        for (int j = N - 1; j > 0; j--) {
            if (temp_map[i][j] == temp_map[i][j - 1]) {
                temp_map[i][j] = temp_map[i][j] * 2;
                temp_map[i][j - 1] = 0;
            }
        }
    }

    // 합치고 나서 생긴 공백 메꾸기
    for (int i = 0; i < N; i++) {
        for (int j = N - 1; j > 0; j--) {
            bool flag = false;
            if (temp_map[i][j] == 0) {
                int k = j - 1;
                while (k >= 0) {
                    if (temp_map[i][k] != 0) {
                        flag = true;
                        break;
                    }
                    k--;
                }
                if (flag) {
                    temp_map[i][j] = temp_map[i][k];
                    temp_map[i][k] = 0;
                }
            }
        }
    }

    MoveUp(cnt + 1, temp_map);
    MoveDown(cnt + 1, temp_map);
    MoveLeft(cnt + 1, temp_map);
    MoveRight(cnt + 1, temp_map);
}

void MoveLeft(int cnt, int copied_map[21][21]) {
    if (cnt == 5) {
        result = max(result, checkBiggestBlock(copied_map));
        return;
    }

    int temp_map[21][21];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            temp_map[i][j] = copied_map[i][j];
        }
    }

    // 빈 칸 먼저 당김. 합치는건 아직 X
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N - 1; j++) {
            bool flag = false;
            if (temp_map[i][j] == 0) {
                int k = j + 1;
                while (k <= N - 1) {
                    if (temp_map[i][k] != 0) {
                        flag = true;
                        break;
                    }
                    k++;
                }
                if (flag) {
                    temp_map[i][j] = temp_map[i][k];
                    temp_map[i][k] = 0;
                }
            }
        }
    }

    // 다음 아랫칸에 같은 크기 블록이 있으면 합친다
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N - 1; j++) {
            if (temp_map[i][j] == temp_map[i][j + 1]) {
                temp_map[i][j] = temp_map[i][j] * 2;
                temp_map[i][j + 1] = 0;
            }
        }
    }

    // 합치고 나서 생긴 공백 메꾸기
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N - 1; j++) {
            bool flag = false;
            if (temp_map[i][j] == 0) {
                int k = j + 1;
                while (k <= N - 1) {
                    if (temp_map[i][k] != 0) {
                        flag = true;
                        break;
                    }
                    k++;
                }
                if (flag) {
                    temp_map[i][j] = temp_map[i][k];
                    temp_map[i][k] = 0;
                }
            }
        }
    }

    MoveUp(cnt + 1, temp_map);
    MoveDown(cnt + 1, temp_map);
    MoveLeft(cnt + 1, temp_map);
    MoveRight(cnt + 1, temp_map);
}

int main() {

    cin >> N;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> map[i][j];
        }
    }

    // 4 ^ 5
    MoveUp(0, map);
    MoveDown(0, map);
    MoveRight(0, map);
    MoveLeft(0, map);

    cout << result;

    return 0;
}