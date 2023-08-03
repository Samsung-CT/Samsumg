#include <cstring>
#include <iostream>
using namespace std;

int R, C, T;
int map[52][52];
int dy[4] = {-1, 1, 0, 0};
int dx[4] = {0, 0, 1, -1};
int cleaner_1_y, cleaner_2_y;

void Debugg() {
    cout << '\n';
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            cout << map[i][j] << " ";
        }
        cout << '\n';
    }
    cout << '\n';
}

bool canSpread(int y, int x) {
    if (y >= 0 && y < R && x >= 0 && x < C) {
        if (map[y][x] != -1)
            return true;
    }

    return false;
}

void Spread() {
    int copied_map[52][52];
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            copied_map[i][j] = map[i][j];
        }
    }

    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (map[i][j] > 0) { // 미세먼지가 있다면
                int cnt = 0;
                int amount = map[i][j] / 5;
                for (int d = 0; d < 4; d++) {
                    int next_y = i + dy[d];
                    int next_x = j + dx[d];
                    if (canSpread(next_y, next_x)) {
                        cnt++;
                        copied_map[next_y][next_x] += amount;
                        copied_map[i][j] -= amount;
                    }
                }
            }
        }
    }

    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            map[i][j] = copied_map[i][j];
        }
    }
}

void CleanClockWise() {
    for (int i = cleaner_1_y; i > 0; i--) {
        map[i][0] = map[i - 1][0];
    }
    for (int i = 0; i < C - 1; i++) {
        map[0][i] = map[0][i + 1];
    }
    for (int i = 0; i < cleaner_1_y; i++) {
        map[i][C - 1] = map[i + 1][C - 1];
    }
    for (int i = C - 1; i > 1; i--) {
        map[cleaner_1_y][i] = map[cleaner_1_y][i - 1];
    }
    map[cleaner_1_y][1] = 0;
    map[cleaner_1_y][0] = -1;
}

void CleanCounterClockWise() {
    for (int i = cleaner_2_y + 1; i < R - 1; i++) {
        map[i][0] = map[i + 1][0];
    }
    for (int i = 0; i < C - 1; i++) {
        map[R - 1][i] = map[R - 1][i + 1];
    }
    for (int i = R - 1; i >= cleaner_2_y; i--) {
        map[i][C - 1] = map[i - 1][C - 1];
    }
    for (int i = C - 1; i > 1; i--) {
        map[cleaner_2_y][i] = map[cleaner_2_y][i - 1];
    }
    map[cleaner_2_y][1] = 0;
}

void Clean() {
    CleanClockWise();
    CleanCounterClockWise();
}

void Circulate() {
    Spread();
    // Debugg();
    Clean();
    // Debugg();
}

void Calculate() {
    int total = 0;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (map[i][j] != -1) {
                total += map[i][j];
            }
        }
    }

    cout << total;
}

int main() {
    cin >> R >> C >> T;

    memset(map, 0, sizeof(map));

    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            cin >> map[i][j];
            if (map[i][j] == -1) {
                cleaner_2_y = i;
            }
        }
    }

    cleaner_1_y = cleaner_2_y - 1;

    for (int i = 0; i < T; i++) {
        Circulate();
    }

    Calculate();

    return 0;
}