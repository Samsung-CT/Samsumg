#include <iostream>
using namespace std;

int N, M;
char map[11][11];
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

int result = 987654321;

void BFS(int cnt, int direction, int red_y, int red_x, int blue_y, int blue_x) {
    int cur_red_y = red_y;
    int cur_red_x = red_x;
    int cur_blue_y = blue_y;
    int cur_blue_x = blue_x;

    if (cnt > 10)
        return;

    while (1) { // 파란구슬 먼저 움직임
        if (map[cur_blue_y + dy[direction]][cur_blue_x + dx[direction]] == 'O') {
            return;
        }
        if (map[cur_blue_y + dy[direction]][cur_blue_x + dx[direction]] == '#')
            break;

        if (map[cur_blue_y + dy[direction]][cur_blue_x + dx[direction]] == '.') {
            cur_blue_y += dy[direction];
            cur_blue_x += dx[direction];
        }
    }

    while (1) { // 빨간 구슬 움직임
        if (map[cur_red_y + dy[direction]][cur_red_x + dx[direction]] == 'O') {
            result = min(result, cnt);
            return;
        }
        if (map[cur_red_y + dy[direction]][cur_red_x + dx[direction]] == '#')
            break;

        if (map[cur_red_y + dy[direction]][cur_red_x + dx[direction]] == '.') {
            cur_red_y += dy[direction];
            cur_red_x += dx[direction];
        }
    }

    for (int i = 0; i < 4; i++) {
        if (i == direction)
            continue;
        BFS(cnt + 1, i, cur_red_y, cur_red_x, cur_blue_y, cur_blue_x);
    }
}

int main() {
    cin >> N >> M;

    int blue_y;
    int blue_x;
    int red_x;
    int red_y;

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
        BFS(1, i, red_y, red_x, blue_x, blue_y);
    }

    if (result == 987654321)
        cout << "-1";
    else
        cout << result;

    return 0;
}