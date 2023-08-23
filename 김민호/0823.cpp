#include <cmath>
#include <iostream>
#define MAX 102
using namespace std;

int N, L;
int map1[MAX][MAX];
int map2[MAX][MAX];

void Input() {
    cin >> N >> L;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> map1[i][j];
            map2[j][i] = map1[i][j];
        }
    }
}

bool buildAvailable(int map[][MAX], int x, int y) {
    int standard = map[x][y + 1];
    for (int j = y + 1; j < y + 1 + L; j++) {
        if (map[x][j] != standard)
            return false;
    }

    return true;
}

int buildRamp(int map[][MAX]) {

    int total = 0;

    for (int i = 0; i < N; i++) {
        int flatland = 1;
        bool can_pass = true;
        for (int j = 0; j < N - 1; j++) {
            if (map[i][j] == map[i][j + 1]) // 평지일때
                flatland++;
            else if (map[i][j] == map[i][j + 1] + 1) { // 내리막길일때
                if (buildAvailable(map, i, j)) {
                    j = j + L - 1; // ?
                    flatland = 0;
                } else {
                    can_pass = false;
                    break;
                }
            } else if (map[i][j] == map[i][j + 1] - 1) { // 오르막길일때
                if (flatland >= L) {
                    flatland = 1;
                } else {
                    can_pass = false;
                    break;
                }
            } else if (abs(map[i][j] - map[i][j + 1]) >= 2) {
                can_pass = false;
                break;
            }
        }

        if (can_pass)
            total++;
    }

    return total;
}

void Solution() {
    int A = buildRamp(map1);
    int B = buildRamp(map2);

    cout << A + B;
}

int main() {
    Input();
    Solution();
}