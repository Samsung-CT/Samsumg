#include <cstring>
#include <iostream>
#include <queue>
using namespace std;

int n;
int map[30][30];
int separated_groups[30][30]; // 그룹을 구분 시킨 맵
bool visited[30][30];
int adjacent[900][900];
int group_colors[900];
int group_cnt[900];
int group_count = 0;
int dy[4] = {1, -1, 0, 0};
int dx[4] = {0, 0, 1, -1};

void Debugg() {
    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < n; j++) {
    //         cout << separated_groups[i][j] << " ";
    //     }
    //     cout << '\n';
    // }

    // for (int i = 1; i <= group_count; i++) {
    //     for (int j = 1; j <= group_count; j++) {
    //         cout << adjacent[i][j] << " ";
    //     }
    //     cout << '\n';
    // }

    // for (int i = 1; i <= group_count; i++) {
    //     cout << group_cnt[i] << " ";
    // }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << map[i][j] << " ";
        }
        cout << '\n';
    }
}

bool inRange(int y, int x) {
    if (y >= 0 && x >= 0 && y < n && x < n)
        return true;

    return false;
}

void rotate(int x, int y) {
    int len = (n - 1) / 2;

    int tmp[30][30] = {
        0,
    };

    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            tmp[j][len - 1 - i] = map[x + i][y + j];
        }
    }

    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            map[x + i][y + j] = tmp[i][j];
        }
    }
}
void rotate() {
    int len = (n - 1) / 2 + 1;

    rotate(0, 0);
    rotate(0, len);
    rotate(len, 0);
    rotate(len, len);

    int tmp[30] = {
        0,
    };
    len -= 1;

    for (int i = 0; i < len; i++)
        tmp[i] = map[i][len];
    for (int i = 0; i < len; i++)
        map[i][len] = map[len][n - 1 - i];
    for (int i = 0; i < len; i++)
        map[len][n - 1 - i] = map[n - 1 - i][len];
    for (int i = 0; i < len; i++)
        map[n - 1 - i][len] = map[len][i];
    for (int i = 0; i < len; i++)
        map[len][i] = tmp[i];
}

// (그룹 a에 속한 칸의 수 + 그룹 b에 속한 칸의 수 ) x 그룹 a를 이루고 있는 숫자 값 x 그룹 b를 이루고 있는 숫자 값 x 그룹 a와 그룹 b가 서로 맞닿아 있는 변의 수
int Calculate() {
    int result = 0;
    for (int i = 1; i <= group_count; i++) {
        for (int j = i + 1; j <= group_count; j++) {
            if (adjacent[i][j] != 0) { // 인접한 두 그룹끼리 계산
                int group1 = i;
                int group2 = j;

                // cout << '\n';
                // cout << "그룹 1 : " << group1 << '\n';
                // cout << "그룹 2 : " << group2 << '\n';
                // cout << "그룹 1에 속한 칸의 수 : " << group_cnt[group1] << '\n';
                // cout << "그룹 2에 속한 칸의 수 : " << group_cnt[group2] << '\n';
                // cout << "그룹 1를 이루고 있는 숫자 값 : " << group_colors[group1] << '\n';
                // cout << "그룹 2를 이루고 있는 숫자 값 : " << group_colors[group2] << '\n';
                // cout << "그룹 1와 그룹 2가 서로 맞닿아 있는 변의 수 : " << adjacent[group1][group2] << '\n';
                // cout << '\n';

                result += (group_cnt[group1] + group_cnt[group2]) * group_colors[group1] * group_colors[group2] * adjacent[group1][group2];
            }
        }
    }

    return result;
}

void CountBFS(int y, int x) {
    queue<pair<int, int>> q;
    q.push(make_pair(y, x));
    visited[y][x] = true;

    while (!q.empty()) {
        int cur_y = q.front().first;
        int cur_x = q.front().second;
        q.pop();

        int cur_group = separated_groups[cur_y][cur_x];
        group_cnt[cur_group]++;

        for (int i = 0; i < 4; i++) {
            int next_y = cur_y + dy[i];
            int next_x = cur_x + dx[i];

            if (inRange(next_y, next_x) && !visited[next_y][next_x]) {
                if (separated_groups[next_y][next_x] == cur_group) {
                    visited[next_y][next_x] = true;
                    q.push(make_pair(next_y, next_x));
                } else {
                    int next_group = separated_groups[next_y][next_x];
                    adjacent[cur_group][next_group]++;
                }
            }
        }
    }
}

void Count() { // 그룹 마다 맞닿아 있는 그룹의 변의 수, 그룹의 수를 계산하여 adjacent[from][to] 에 저장
    memset(visited, false, sizeof(visited));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!visited[i][j]) {
                CountBFS(i, j);
            }
        }
    }
}

void BFS(int y, int x) { // 맵을 separated map 으로 구분시키는 함수
    queue<pair<int, int>> q;
    q.push(make_pair(y, x));
    visited[y][x] = true;
    separated_groups[y][x] = group_count;
    while (!q.empty()) {
        int cur_y = q.front().first;
        int cur_x = q.front().second;
        q.pop();

        for (int i = 0; i < 4; i++) {
            int next_y = cur_y + dy[i];
            int next_x = cur_x + dx[i];

            if (inRange(next_y, next_x) && !visited[next_y][next_x]) {
                if (map[next_y][next_x] == map[cur_y][cur_x]) {
                    separated_groups[next_y][next_x] = group_count;
                    visited[next_y][next_x] = true;
                    q.push(make_pair(next_y, next_x));
                }
            }
        }
    }
}

void NumberGroups() { // 맵을 separated map 으로 구분시키는 함수
    memset(visited, false, sizeof(visited));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!visited[i][j]) {
                group_count++;                         // 새로운 그룹 발견
                group_colors[group_count] = map[i][j]; // 그룹의 색깔 저장
                BFS(i, j);
            }
        }
    }
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> map[i][j];
        }
    }

    int result = 0;

    for (int i = 0; i < 4; i++) {
        NumberGroups(); // 맵의 그룹을 구분시킴
        Count();
        result = max(result, Calculate());
        if (i != 3)
            rotate();
    }

    // Debugg();

    cout << result;

    return 0;
}