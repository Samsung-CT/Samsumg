#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// 1. 크기가 가장 큰 블록 그룹을 찾는다. 그러한 블록 그룹이 여러 개라면 포함된 무지개 블록의 수가 가장 많은 블록 그룹,
// 그러한 블록도 여러개라면 기준 블록의 행이 가장 큰 것을,
// 그것도 여러개이면 열이 가장 큰 것을 찾는다.
// 2. 1에서 찾은 블록 그룹의 모든 블록을 제거한다. 블록 그룹에 포함된 블록의 수를 B라고 했을 때, B^2점을 획득한다.
// 3. 격자에 중력이 작용한다.
// 4. 격자가 90도 반시계 방향으로 회전한다.
// 5. 다시 격자에 중력이 작용한다.

int map[21][21];
bool visited[21][21];
int dy[4] = {-1, 1, 0, 0};
int dx[4] = {0, 0, 1, -1};
int N, M;
int result = 0;

struct BLOCKS {
    pair<int, int> top;
    int rainbow_cnt;
    int color_block_cnt;
};

void Reset() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (map[i][j] == 0 && visited[i][j]) {
                visited[i][j] = false;
            }
        }
    }
}

void Debugg() {
    cout << '\n';
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << map[i][j] << " ";
        }
        cout << '\n';
    }
}
// 크기가 가장 큰 블록 그룹을 찾는다. 그러한 블록 그룹이 여러 개라면 포함된 무지개 블록의 수가 가장 많은 블록 그룹, 그러한 블록도 여러개라면 기준 블록의 행이 가장 큰 것을, 그 것도
// 여러개이면 열이 가장 큰 것을 찾는다.
bool compare(const BLOCKS &b1, const BLOCKS &b2) {
    if (b1.color_block_cnt + b1.rainbow_cnt == b2.color_block_cnt + b2.rainbow_cnt) {
        if (b1.rainbow_cnt == b2.rainbow_cnt) {
            if (b1.top.first == b2.top.first) {
                return b1.top.second > b2.top.second;
            } else
                return b1.top.first > b2.top.first;
        } else
            return b1.rainbow_cnt > b2.rainbow_cnt;
    } else
        return b1.color_block_cnt + b1.rainbow_cnt > b2.color_block_cnt + b2.rainbow_cnt;
}

bool inRange(int y, int x) {
    if (y >= 0 && x >= 0 && y < N && x < N)
        return true;

    return false;
}

void Gravity() {
    for (int i = N - 2; i >= 0; i--) {
        for (int j = 0; j < N; j++) {
            if (map[i][j] == -2)
                continue;
            if (map[i][j] == -1)
                continue;

            int color = map[i][j];
            int next_y = i + 1;

            while (1) {
                if (map[next_y][j] != -2)
                    break;
                if (next_y == N)
                    break;
                next_y++;
            }

            next_y--;
            map[i][j] = -2;
            map[next_y][j] = color;
        }
    }
}

void Rotate() {
    int temp_map[N][N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            temp_map[N - 1 - j][i] = map[i][j];
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            map[i][j] = temp_map[i][j];
        }
    }
}

void Remove(int y, int x) { // 블록 그룹 제거하고 점수 획득
    memset(visited, false, sizeof(visited));
    queue<pair<int, int>> q;
    visited[y][x] = true;
    q.push(make_pair(y, x));
    int color = map[y][x];
    map[y][x] = -2;
    int points = 1;

    while (!q.empty()) {
        int cur_y = q.front().first;
        int cur_x = q.front().second;

        q.pop();

        for (int i = 0; i < 4; i++) {
            int next_y = cur_y + dy[i];
            int next_x = cur_x + dx[i];

            if (inRange(next_y, next_x) && !visited[next_y][next_x]) {
                if (map[next_y][next_x] == color || map[next_y][next_x] == 0) { // 같은 색깔의 벽돌이거나 무지개 색깔의 벽돌이면
                    visited[next_y][next_x] = true;
                    q.push(make_pair(next_y, next_x));
                    map[next_y][next_x] = -2;
                    points++;
                }
            }
        }
    }
    // cout << (points * points) << '\n';
    result += (points * points);
}

BLOCKS BFS(int y, int x) {
    queue<pair<int, int>> q;
    q.push(make_pair(y, x));
    visited[y][x] = true;
    int color = map[y][x];
    pair<int, int> top = make_pair(y, x);
    int rainbow_cnt = 0;
    int color_block_cnt = 1;

    while (!q.empty()) {
        int cur_y = q.front().first;
        int cur_x = q.front().second;
        q.pop();

        for (int i = 0; i < 4; i++) {
            int next_y = cur_y + dy[i];
            int next_x = cur_x + dx[i];

            if (inRange(next_y, next_x) && !visited[next_y][next_x]) {
                if (map[next_y][next_x] == color) { // 같은 색깔의 벽돌이면
                    visited[next_y][next_x] = true;
                    color_block_cnt++;
                    q.push(make_pair(next_y, next_x));
                    if (top.first > next_y) {
                        top.first = next_y;
                        top.second = next_x;
                    } else if (top.first == next_y && top.second > next_x) {
                        top.second = next_x;
                    }
                } else if (map[next_y][next_x] == 0) { // 무지개 색깔의 벽돌이면
                    visited[next_y][next_x] = true;
                    rainbow_cnt++;
                    q.push(make_pair(next_y, next_x));
                }
            }
        }
    }

    BLOCKS block = {top, rainbow_cnt, color_block_cnt};

    return block;
}

bool Search() {
    memset(visited, false, sizeof(visited));
    vector<BLOCKS> b;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (!visited[i][j] && map[i][j] > 0) {
                Reset();
                BLOCKS temp = BFS(i, j);
                if (temp.color_block_cnt + temp.rainbow_cnt >= 2) {
                    b.push_back(temp);
                }
            }
        }
    }

    if (b.size() == 0) {
        return false;
    }

    sort(b.begin(), b.end(), compare);

    Remove(b.front().top.first, b.front().top.second);
    // Debugg();
    Gravity();
    // Debugg();
    Rotate();
    // Debugg();
    Gravity();
    // Debugg();

    return true;
}

int main() {

    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> map[i][j];
        }
    }

    bool flag = true;
    while (flag) {
        flag = Search();
    }

    cout << result;
    return 0;
}