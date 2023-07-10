#include <cstring>
#include <iostream>
#include <queue>
using namespace std;

int map[21][21];
bool visited[21][21];
int dy[4] = {-1, 1, 0, 0};
int dx[4] = {0, 0, 1, -1};
int N;

typedef struct {
    int y;
    int x;
    int eat_num;
    int time;
    int size;
} Shark;

typedef struct {
    int y;
    int x;
    int size;
} Fish;

Shark S;                                      // 현재 상어의 info
priority_queue<pair<int, pair<int, int>>> pq; // 현재 상어 위치에서 물고기들의 거리, y, x

void Debugg() {
    cout << "좌표 :" << S.y << ", " << S.x << '\n';
    cout << "먹은 물고기 수: " << S.eat_num << '\n';
    cout << "걸린시간: " << S.time << '\n';
    cout << "현재 물고기 크기: " << S.size << '\n';
    cout << '\n';
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << map[i][j] << " ";
        }
        cout << '\n';
    }
    cout << '\n';
}

bool inRange(int y, int x) {
    if (x >= 0 && y >= 0 && x < N && y < N)
        return true;

    return false;
}

void BFS(int y, int x) {                // 현재 아기상어의 위치에서 시작해서 가장 가까운 물고기를 찾는 함수
    queue<pair<int, pair<int, int>>> q; // 현재 탐색 중인 상어가 이동한 거리, y, x 좌표
    q.push(make_pair(0, make_pair(y, x)));
    visited[y][x] = true;
    int cur_y;
    int cur_x;
    int cur_dist;

    while (!q.empty()) {
        cur_y = q.front().second.first;
        cur_x = q.front().second.second;
        cur_dist = q.front().first;
        q.pop();

        for (int i = 0; i < 4; i++) {
            int next_y = cur_y + dy[i];
            int next_x = cur_x + dx[i];

            if (inRange(next_y, next_x) && !visited[next_y][next_x]) {
                if (map[next_y][next_x] == 0) {     // 빈칸이면
                    visited[next_y][next_x] = true; // 이동
                    q.push(make_pair(cur_dist + 1, make_pair(next_y, next_x)));
                } else if (map[next_y][next_x] < S.size) { // 아기상어보다 작은 물고기를 발견하면
                    visited[next_y][next_x] = true;
                    pq.push(make_pair(-(cur_dist + 1), make_pair(-next_y, -next_x)));
                } else if (map[next_y][next_x] == S.size) { // 아기상어와 같은 크기의 물고기를 발견하면
                    visited[next_y][next_x] = true;
                    q.push(make_pair(cur_dist + 1, make_pair(next_y, next_x)));
                }
            }
        }
    }
}

void Solve() {
    while (1) {
        pq = priority_queue<pair<int, pair<int, int>>>();
        memset(visited, false, sizeof(visited));

        BFS(S.y, S.x);

        if (pq.size() == 0) {
            cout << S.time;
            break;
        }

        // pq 의 첫번째 원소는 아기상어가 먹을 수 있는 가장 가까운 물고기이다.
        int fish_y = -pq.top().second.first;
        int fish_x = -pq.top().second.second;
        int dist = -pq.top().first;

        S.time += dist;
        S.eat_num++;
        if (S.eat_num == S.size) { // 자신의 크기와 같은 수량의 물고기를 먹을떄마다 크기가 1 증가
            S.size++;
            S.eat_num = 0;
        }

        map[S.y][S.x] = 0;

        S.y = fish_y;
        S.x = fish_x;
        map[S.y][S.x] = 9;

        // Debugg();
    }
}

int main() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> map[i][j];
            if (map[i][j] == 9) {
                S.y = i;
                S.x = j;
                S.eat_num = 0;
                S.time = 0;
                S.size = 2;
            }
        }
    }

    Solve();

    return 0;
}