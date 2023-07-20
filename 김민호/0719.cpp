#include <algorithm>
#include <iostream>
using namespace std;

// ! 기울이는 동작을 그만 하는 것은 구슬이 움직이지 않을때

// 1. 빨간 공을 진행방향으로 움직인다. 이 과정에서 빨간공이 구멍에 빠지게 되면 구멍에 빠졌다고 표시
// 2. 파란 공이 진행방향으로 움직인다. 이 과정에서 파란공이 구멍에 빠지게 되면 구멍에 빠졌다고 표시
// 3. 파란공이 구멍에 빠졌다면 함수를 끝내준다.
// 4. 파란공이 구멍에 빠지지 않았는데 빨간공이 빠졌다면 기존의 기울인 횟수와 비교해서 값을 갱신시켜준다.
// 5. 위 경우가 모두 아니라면 그 어떤 공도 구멍에 빠지지 않았다면 빨간공과 파란공의 좌표를 비교해준다
// 6. 빨간공과 파란공이 겹치면 빨간공과 파란공의 움직인 거리중 더 많이 움직인 공을 한칸 뒤로 땡겨준다(겹칠 수 없기 때문에)

int N, M;
char map[11][11];
int dy[4] = {-1, 1, 0, 0};
int dx[4] = {0, 0, 1, -1};
int answer = 987654321;

int ReverseDirection(int direction) {
    if (direction == 0)
        return 1;
    else if (direction == 1)
        return 0;
    else if (direction == 2)
        return 3;
    else if (direction == 3)
        return 2;
    else
        return -1;
}

void Roll(int red_y, int red_x, int blue_y, int blue_x, int direction, int cnt) {
    if (cnt > 10)
        return;
    if (cnt >= answer)
        return;

    int cur_red_y = red_y;
    int cur_red_x = red_x;
    int cur_blue_y = blue_y;
    int cur_blue_x = blue_x;

    bool red_flag = false;
    bool blue_flag = false;
    int red_distance = 0;
    int blue_distance = 0;

    // direction 방향으로 빨간 구슬을 벽 끝까지 이동 시킨다
    while (1) {
        int next_red_y = cur_red_y + dy[direction];
        int next_red_x = cur_red_x + dx[direction];

        if (map[next_red_y][next_red_x] == '#') // 다음칸이 벽이면 더이상 진행하지 않는다
            break;

        if (map[next_red_y][next_red_x] == 'O') { // 다음칸이 구멍이면
            red_flag = true;
            break;
        }

        cur_red_y = next_red_y;
        cur_red_x = next_red_x;
        red_distance++;
    }

    // direction 방향으로 빨간 구슬을 벽 끝까지 이동 시킨다
    while (1) {
        int next_blue_y = cur_blue_y + dy[direction];
        int next_blue_x = cur_blue_x + dx[direction];

        if (map[next_blue_y][next_blue_x] == '#')
            break;

        if (map[next_blue_y][next_blue_x] == 'O') {
            blue_flag = true;
            break;
        }

        cur_blue_y = next_blue_y;
        cur_blue_x = next_blue_x;
        blue_distance++;
    }

    if (blue_flag) // 파란공 빠졌으면 리턴
        return;
    else if (red_flag && !blue_flag) { // 빨간공만 빠졌으면
        answer = min(answer, cnt);
        return;
    }

    if (cur_red_y == cur_blue_y && cur_red_x == cur_blue_x) { // 굴렷는데 둘다 벽에 부딪히면 적게 움직인 구슬 한칸 후퇴
        if (red_distance > blue_distance) {
            cur_red_y -= dy[direction];
            cur_red_x -= dx[direction];
        } else {
            cur_blue_y -= dy[direction];
            cur_blue_x -= dx[direction];
        }
    }

    int reverse_direction = ReverseDirection(direction);
    for (int i = 0; i < 4; i++) {
        if (i == reverse_direction || i == direction)
            continue;
        Roll(cur_red_y, cur_red_x, cur_blue_y, cur_blue_x, i, cnt + 1);
    }
}

int main() {
    int red_y, red_x, blue_y, blue_x;
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        string temp;
        cin >> temp;
        for (int j = 0; j < temp.length(); j++) {
            map[i][j] = temp[j];
            if (map[i][j] == 'R') {
                red_y = i;
                red_x = j;
            } else if (map[i][j] == 'B') {
                blue_y = i;
                blue_x = j;
            }
        }
    }

    for (int i = 0; i < 4; i++) {
        Roll(red_y, red_x, blue_y, blue_x, i, 1);
    }

    if (answer == -1 || answer == 987654321) {
        cout << "-1";
    } else {
        cout << answer;
    }

    return 0;
}