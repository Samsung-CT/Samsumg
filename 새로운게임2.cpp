#include <deque>
#include <iostream>
#include <vector>
using namespace std;

int N, K;
int dy[5] = {0, 0, 0, -1, 1}; //  →, ←, ↑, ↓
int dx[5] = {0, 1, -1, 0, 0}; //  →, ←, ↑, ↓

deque<int> map[13][13];
int map_color[13][13];                  // 0: 흰색, 1: 빨간색, 2: 파란색
pair<pair<int, int>, int> location[12]; // y, x, direction
int result = 0;
bool flag = true;

void Debugg() {
    for (int i = 1; i <= K; i++) {
        cout << i << " : " << location[i].first.first << " " << location[i].first.second << " " << location[i].second << '\n';
    }
    cout << '\n';
}

bool inRange(int y, int x) {
    if (y >= 1 && x >= 1 && x <= N && y <= N)
        return true;

    return false;
}

int getOppositeDirection(int direction) {
    if (direction == 1)
        return 2;
    else if (direction == 2)
        return 1;
    else if (direction == 3)
        return 4;
    else
        return 3;
}

void Move(int chess) {
    int cur_y = location[chess].first.first;
    int cur_x = location[chess].first.second;
    int direction = location[chess].second;

    if (map[cur_y][cur_x].size() >= 4)
        flag = false;

    int next_y = cur_y + dy[direction];
    int next_x = cur_x + dx[direction];

    int index;

    for (int i = 0; i < map[cur_y][cur_x].size(); i++) {
        if (map[cur_y][cur_x][i] == chess) {
            index = i;
        }
    }

    if (map_color[next_y][next_x] == 0 && inRange(next_y, next_x)) { // 흰색인경우
        location[chess].first.first = next_y;                        // 그 칸으로 이동
        location[chess].first.second = next_x;

        for (int i = index; i < map[cur_y][cur_x].size(); i++) {
            int temp = map[cur_y][cur_x][i];
            map[next_y][next_x].push_back(temp);
            location[temp].first.first = next_y;
            location[temp].first.second = next_x;
        }

        int temp_size = map[cur_y][cur_x].size();
        for (int i = index; i < temp_size; i++) {
            map[cur_y][cur_x].pop_back();
        }

        if (map[next_y][next_x].size() >= 4) {
            flag = false;
        }

    } else if (map_color[next_y][next_x] == 1 && inRange(next_y, next_x)) { // 빨간색인경우
        location[chess].first.first = next_y;                               // 그 칸으로 이동
        location[chess].first.second = next_x;

        for (int i = map[cur_y][cur_x].size() - 1; i >= index; i--) {
            int temp = map[cur_y][cur_x][i];
            map[next_y][next_x].push_back(temp);
            location[temp].first.first = next_y;
            location[temp].first.second = next_x;
        }
        int temp_size = map[cur_y][cur_x].size() - 1;
        for (int i = temp_size; i >= index; i--) {
            map[cur_y][cur_x].pop_back();
        }

        if (map[next_y][next_x].size() >= 4) {
            flag = false;
        }

    } else { // 파란색인경우이거나 맵밖으로 체스판을 벗어나는 경우
        int next_blue_direction = getOppositeDirection(direction);
        location[chess].second = next_blue_direction;
        int next_blue_y = cur_y + dy[next_blue_direction];
        int next_blue_x = cur_x + dx[next_blue_direction];

        if (map_color[next_blue_y][next_blue_x] != 2 && inRange(next_blue_y, next_blue_x)) {
            Move(chess);
        }

        if (map[next_blue_y][next_blue_x].size() >= 4) {
            flag = false;
        }
    }
}

void Solve() {
    while (result != 1001 && flag) {
        for (int i = 1; i <= K; i++) {
            Move(i);
            // Debugg();
            if (flag == false)
                break;
        }
        result++;
    }

    if (result == 1001) {
        cout << "-1";
    } else {
        cout << result;
    }
}

int main() {
    cin >> N >> K;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cin >> map_color[i][j];
        }
    }

    for (int i = 1; i <= K; i++) {
        int y, x, direction;
        cin >> y >> x >> direction;
        location[i] = make_pair(make_pair(y, x), direction);
        map[y][x].push_back(i);
    }

    Solve();

    return 0;
}
