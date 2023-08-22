#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int n, m, t, k;
int dy[4] = {-1, 1, 0, 0};
int dx[4] = {0, 0, 1, -1};
vector<int> map[51][51];

struct BALL {
    int index;
    int y;
    int x;
    int direction;
    int speed;
    bool alive;
};

vector<BALL> balls(2502);

void Debugg() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (map[i][j].size() > 0)
                cout << map[i][j][0] << " ";
            else
                cout << "0 ";
        }
        cout << '\n';
    }
    cout << '\n';
}

// 구슬의 속도가 빠른 구슬일수록 우선순위가 높으며 구슬의 속도가 일치할 경우에는 구슬의 번호가 더 큰 구슬이 우선순위가 높습니다.
bool cmp(const int &ball1, const int &ball2) {
    if (balls[ball1].speed == balls[ball2].speed) {
        if (balls[ball1].index > balls[ball2].index)
            return ball1 > ball2;
        else
            return ball1 < ball2;
    } else
        return ball1 > ball2;
}

void MapUpdate() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (map[i][j].size() > k) {
                sort(map[i][j].begin(), map[i][j].end(), cmp);

                for (int b = k; b < map[i][j].size(); b++) {
                    int ball = map[i][j].back();
                    balls[ball].alive = false;
                    map[i][j].pop_back();
                }
            }
        }
    }
}

int ReverseDirection(int direction) {
    if (direction == 0)
        return 1;
    else if (direction == 1)
        return 0;
    else if (direction == 2)
        return 3;
    else
        return 2;
}

bool inRange(int y, int x) {
    if (y >= 1 && x >= 1 && y <= n && x <= n)
        return true;

    return false;
}

void Roll() {
    for (int i = 1; i < balls.size(); i++) {
        if (balls[i].index == i) {
            cout << i << " 움직임! \n";
            int init_y = balls[i].y;
            int init_x = balls[i].x;
            int cur_y = balls[i].y;
            int cur_x = balls[i].x;
            int cur_direction = balls[i].direction;
            int speed = balls[i].speed;

            // cout << cur_y << " " << cur_x << '\n';

            // i번 구슬의 움직임
            for (int time = 0; time < speed; time++) {
                int next_y = cur_y + dy[cur_direction];
                int next_x = cur_x + dx[cur_direction];

                if (inRange(next_y, next_x)) {
                    // balls[i].y = next_y;
                    // balls[i].x = next_x;
                    cur_y = next_y;
                    cur_x = next_x;
                } else {
                    cur_direction = ReverseDirection(cur_direction);
                    cur_y += dy[cur_direction];
                    cur_x += dx[cur_direction];
                }
                // cout << cur_y << " " << cur_x << " \n";
            }

            int SIZE = map[init_y][init_x].size() % k;
            for (int b = 0; b < SIZE; b++) {
                // cout << "! \n";
                if (map[init_y][init_x][b] == balls[i].index) {
                    // cout << "찾았다! \n";
                    map[init_y][init_x].erase(map[init_y][init_x].begin() + b); // map 에서 움직인 구슬 삭제
                    break;
                }
            }

            // map 정보와 구슬 정보 업데이트
            balls[i].y = cur_y;
            balls[i].x = cur_x;
            balls[i].direction = cur_direction;
            map[cur_y][cur_x].push_back(i);

            Debugg();
        }
    }
    MapUpdate();
    // Debugg();
}

int main() {
    // 여기에 코드를 작성해주세요.
    cin >> n >> m >> t >> k; // 격자의 크기를 나타내는 n과 구슬의 개수를 나타내는 m, 시간 t, 그리고 각 칸에 살아남을 수 있는 최대 구슬 수를 의미하는 k
    for (int i = 1; i <= m; i++) {
        int r, c, d, v;
        char direction;
        cin >> r >> c >> direction >> v;
        if (direction == 'U') {
            d = 0;
        } else if (direction == 'D') {
            d = 1;
        } else if (direction == 'R') {
            d = 2;
        } else {
            d = 3;
        }
        map[r][c].push_back(i);
        balls[i] = {i, r, c, d, v, true};
    }

    // Debugg();

    for (int i = 0; i < t; i++) {
        Roll();
    }

    int result = 0;
    for (int i = 0; i < balls.size(); i++) {
        if (balls[i].alive)
            result++;
    }

    cout << result;

    return 0;
}