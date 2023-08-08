// 백준이 태울 승객을 고를 때는 현재 위치에서 최단거리가 가장 짧은 승객을 고른다.
// 그런 승객이 여러 명이면 그중 행 번호가 가장 작은 승객을, 그런 승객도 여러 명이면 그중 열 번호가 가장 작은 승객을 고른다.
// 택시와 승객이 같은 위치에 서 있으면 그 승객까지의 최단거리는 0이다.
// 연료는 한 칸 이동할 때마다 1만큼 소모된다.
// 한 승객을 목적지로 성공적으로 이동시키면, 그 승객을 태워 이동하면서 소모한 연료 양의 두 배가 충전된다.
// 이동하는 도중에 연료가 바닥나면 이동에 실패하고, 그 날의 업무가 끝난다. 승객을 목적지로 이동시킨 동시에 연료가 바닥나는 경우는 실패한 것으로 간주하지 않는다.

#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int N, M, initial_fuel; // N * N 의 격자, M 명의 승객, 초기 연료
int Map[21][21];
bool visited[21][21];
int dist[21][21];
int taxi_y, taxi_x;

int dy[4] = {0, 0, 1, -1};
int dx[4] = {1, -1, 0, 0};

struct CUSTOMER {
    int start_y;
    int start_x;
    int end_y;
    int end_x;
};

struct INFO {
    int distance;
    int index;
    int y;
    int x;
};

CUSTOMER customer[500];

bool inRange(int y, int x) {
    if (y >= 1 && x >= 1 && y <= N && x <= N)
        return true;

    return false;
}

bool cmp(INFO customer1, INFO customer2) {
    if (customer1.distance <= customer2.distance) {
        if (customer1.distance <= customer2.distance) {
            if (customer1.y <= customer2.y) {
                if (customer1.y == customer2.y) {
                    if (customer1.x < customer2.x) {
                        return true;
                    }
                    return false;
                }
                return true;
            }
            return false;
        }
        return true;
    }
    return false;
}

int toDestination(int index) { // 목적지까지 거리를 구함
    int dest_y = customer[index].end_y;
    int dest_x = customer[index].end_x;
    // cout << "목적지 : " << dest_y << " " << dest_x << '\n';
    // cout << "현재 위치 : " << taxi_y << " " << taxi_x << '\n';
    memset(visited, false, sizeof(visited));
    queue<pair<pair<int, int>, pair<int, int>>> q; // y, x, distance, fuel
    visited[taxi_y][taxi_x] = true;
    q.push(make_pair(make_pair(taxi_y, taxi_x), make_pair(0, initial_fuel)));

    while (!q.empty()) {
        int cur_y = q.front().first.first;
        int cur_x = q.front().first.second;
        int distance = q.front().second.first;
        int fuel = q.front().second.second;

        q.pop();

        if (fuel < 0) {
            continue;
        }

        if (cur_y == dest_y && cur_x == dest_x) { // 목적지에 도착하면
            initial_fuel -= distance;
            initial_fuel += distance * 2;
            taxi_y = cur_y;
            taxi_x = cur_x;
            // cout << index << " 목적지에 도착하였습니다 \n";
            return true;
        }

        for (int i = 0; i < 4; i++) {
            int next_y = cur_y + dy[i];
            int next_x = cur_x + dx[i];

            if (inRange(next_y, next_x) && !visited[next_y][next_x]) {
                if (Map[next_y][next_x] != -1) {
                    visited[next_y][next_x] = true;
                    q.push(make_pair(make_pair(next_y, next_x), make_pair(distance + 1, fuel - 1)));
                }
            }
        }
    }

    return false;
}

int findShortestCustomer() { // 현재 위치에서 가장 가까운 승객을 찾음
    queue<pair<pair<int, int>, pair<int, int>>> q;
    q.push(make_pair(make_pair(taxi_y, taxi_x), make_pair(0, initial_fuel))); // 현재 택시 위치 [y,x] , 이동거리, 남은 연료량
    memset(visited, false, sizeof(visited));
    visited[taxi_y][taxi_x] = true;

    vector<INFO> available_customers; // 도착가능한 승객까지 거리, y,x, 승객번호, 거리
    // 모두 넣어줘야 함. 같은 거리의 경우, 비교해줘야 하기 때문에

    while (!q.empty()) {

        int cur_y = q.front().first.first;
        int cur_x = q.front().first.second;
        int distance = q.front().second.first;
        int fuel = q.front().second.second;

        q.pop();

        if (fuel < 0) // 연료 다 썼으면 더이상 가지 않음
            continue;

        if (Map[cur_y][cur_x] >= 1)
            available_customers.push_back({distance, Map[cur_y][cur_x], cur_y, cur_x});

        for (int i = 0; i < 4; i++) {
            int next_y = cur_y + dy[i];
            int next_x = cur_x + dx[i];

            if (inRange(next_y, next_x) && !visited[next_y][next_x]) {
                if (Map[next_y][next_x] != -1) {
                    visited[next_y][next_x] = true;
                    q.push(make_pair(make_pair(next_y, next_x), make_pair(distance + 1, fuel - 1)));
                }
            }
        }
    }

    if (available_customers.size() == 0)
        return -1;

    sort(available_customers.begin(), available_customers.end(), cmp);
    Map[available_customers[0].y][available_customers[0].x] = 0; // 승객 태우고 승객 맵에서 지우기
    taxi_y = available_customers[0].y;                           // 택시 위치 갱신
    taxi_x = available_customers[0].x;
    initial_fuel -= available_customers[0].distance;

    // cout << available_customers[0].index << " 를 태웠습니다 \n";
    return available_customers[0].index;
}

int main() {
    cin >> N >> M >> initial_fuel;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            int map_info;
            cin >> map_info;
            if (map_info == 1) {
                Map[i][j] = -1; // 벽을 1이 아닌 -1 로 표시
            } else {
                Map[i][j] = 0;
            }
        }
    }

    cin >> taxi_y >> taxi_x;

    for (int i = 1; i <= M; i++) {
        int start_y, start_x, end_y, end_x;
        cin >> start_y >> start_x >> end_y >> end_x;
        customer[i] = {start_y, start_x, end_y, end_x};
        Map[start_y][start_x] = i;
    }

    for (int i = 0; i < M; i++) { // 승객의 수만큼 이동해보고 승객의 수만큼 이동하지 못하면 -1 출력
        int result1 = findShortestCustomer();
        if (result1 == -1) {
            initial_fuel = -1;
            break;
        }
        bool result2 = toDestination(result1);
        if (!result2) {
            initial_fuel = -1;
            break;
        }
    }

    cout << initial_fuel;

    return 0;
}
