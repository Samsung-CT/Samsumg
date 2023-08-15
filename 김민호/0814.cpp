#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;

int N, Q;
int map[65][65];
bool visited[65][65];
int dy[4] = {-1, 1, 0, 0};
int dx[4] = {0, 0, 1, -1};
int row;

void Debugg() {
    cout << '\n';
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < row; j++) {
            cout << map[i][j] << " ";
        }
        cout << '\n';
    }
}

bool inRange(int y, int x) {
    if (y >= 0 && x >= 0 && y < row && x < row)
        return true;

    return false;
}

int BFS(int y, int x) {
    int area_count = 1;
    queue<pair<int, int>> q;
    visited[y][x] = true;
    q.push(make_pair(y, x));

    while (!q.empty()) {
        int cur_y = q.front().first;
        int cur_x = q.front().second;
        q.pop();

        for (int i = 0; i < 4; i++) {
            int next_y = cur_y + dy[i];
            int next_x = cur_x + dx[i];

            if (inRange(next_y, next_x) && !visited[next_y][next_x]) {
                if (map[next_y][next_x] != 0) {
                    visited[next_y][next_x] = true;
                    q.push({next_y, next_x});
                    area_count++;
                }
            }
        }
    }
    return area_count;
}

// 남아있는 얼음 A[r][c]의 합
int CountIce() {
    int result = 0;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < row; j++) {
            if (map[i][j] != 0)
                result += map[i][j];
        }
    }

    return result;
}

// 남아있는 얼음 중 가장 큰 덩어리가 차지하는 칸의 개수
int CountArea() {
    int max_area = 0;
    memset(visited, false, sizeof(visited));
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < row; j++) {
            if (map[i][j] != 0 && !visited[i][j]) {
                max_area = max(max_area, BFS(i, j));
            }
        }
    }

    return max_area;
}

void RotateBox(int y, int x, int len) {
    int retBox[len][len];

    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            retBox[j][len - 1 - i] = map[y + i][x + j];
        }
    }

    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            map[y + i][x + j] = retBox[i][j];
        }
    }
}

void Rotate(int L) {
    int box = row / pow(2, L);
    int len = pow(2, L);

    for (int i = 0; i < box; i++) {
        for (int j = 0; j < box; j++) {
            int y = i * len;
            int x = j * len;

            RotateBox(y, x, len);
        }
    }
}

void Melt() {
    vector<pair<int, int>> willMelt;

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < row; j++) {
            int cnt = 0;
            if (map[i][j] == 0)
                continue;
            for (int k = 0; k < 4; k++) {
                int next_y = i + dy[k];
                int next_x = j + dx[k];

                if (inRange(next_y, next_x) && map[next_y][next_x] > 0)
                    cnt++;
            }
            if (cnt < 3) {
                willMelt.push_back({i, j});
            }
        }
    }

    for (int i = 0; i < willMelt.size(); i++) {
        map[willMelt[i].first][willMelt[i].second]--;
    }
}

void FireStorm(int stage) {
    // cout << "L : " << stage << '\n';
    // cout << "Rotate : \n";
    Rotate(stage);
    // Debugg();
    // cout << "Melt : \n";
    Melt();
    // Debugg();
}

int main() {
    cin >> N >> Q;
    row = pow(2, N);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < row; j++) {
            cin >> map[i][j];
        }
    }

    for (int i = 0; i < Q; i++) {
        int L;
        cin >> L;
        FireStorm(L);
    }

    int total_ice_cnt, max_ice_area;
    total_ice_cnt = CountIce();
    max_ice_area = CountArea();

    if (total_ice_cnt == 0) {
        cout << "0" << '\n';
        cout << "0" << '\n';
    } else {
        cout << total_ice_cnt << '\n';
        cout << max_ice_area;
    }

    return 0;
}