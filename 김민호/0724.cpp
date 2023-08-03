#include <iostream>
#include <vector>
using namespace std;

// 1. 낚시왕이 오른쪽으로 한 칸 이동한다.
// 2. 낚시왕이 있는 열에 있는 상어 중에서 땅과 제일 가까운 상어를 잡는다. 상어를 잡으면 격자판에서 잡은 상어가 사라진다.
// 3. 상어가 이동한다.
int R, C, M; // 격자판의 크기 R,C, 상어의 수 M
int result = 0;
struct SharkInfo {
    int r;
    int c;
    int speed;
    int direction;
    int size;
    int index;
    bool alive;
};

vector<SharkInfo> sharks;
pair<int, int> Map[102][102]; // size, index
int dy[5] = {0, -1, 1, 0, 0};
int dx[5] = {0, 0, 0, 1, -1};

void Init() {
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            Map[i][j] = make_pair(-1, -1);
        }
    }
}

void Debugg() {
    cout << '\n';
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            cout << Map[i][j].second << " ";
        }
        cout << '\n';
    }
}

bool inRange(int y, int x) {
    if (y >= 1 && y <= R && x >= 1 && x <= C)
        return true;

    return false;
}

int ReverseDirection(int direction) {
    if (direction == 1)
        return 2;
    else if (direction == 2)
        return 1;
    else if (direction == 3)
        return 4;
    else if (direction == 4)
        return 3;

    return 0;
}

void MoveSharks() {
    for (int i = 0; i < sharks.size(); i++) {
        if (sharks[i].alive) { // 살아 있는 상어들을 차례대로 이동
            Map[sharks[i].r][sharks[i].c].first = -1;
            Map[sharks[i].r][sharks[i].c].second = -1;
            for (int j = 0; j < sharks[i].speed; j++) {
                int next_y = sharks[i].r + dy[sharks[i].direction];
                int next_x = sharks[i].c + dx[sharks[i].direction];

                if (inRange(next_y, next_x)) { // 다음 칸이 격자 안이면
                    sharks[i].r = next_y;
                    sharks[i].c = next_x;
                } else { // 다음 칸이 격자를 벗어나면
                    int reversed_direction = ReverseDirection(sharks[i].direction);
                    sharks[i].direction = reversed_direction;
                    next_y = sharks[i].r + dy[sharks[i].direction];
                    next_x = sharks[i].c + dx[sharks[i].direction];

                    sharks[i].r = next_y;
                    sharks[i].c = next_x;
                }
            }
        }
    }

    Init();

    for (int i = 0; i < sharks.size(); i++) {
        if (sharks[i].alive) {
            if (Map[sharks[i].r][sharks[i].c].first == -1 && Map[sharks[i].r][sharks[i].c].first == -1) {
                Map[sharks[i].r][sharks[i].c].first = sharks[i].size;
                Map[sharks[i].r][sharks[i].c].second = sharks[i].index;
            } else if (Map[sharks[i].r][sharks[i].c].first > sharks[i].size) { // 이동하려는 위치에 더 큰 상어가 있다면
                sharks[i].alive = false;
            } else if (Map[sharks[i].r][sharks[i].c].first < sharks[i].size) { // 이동하려는 위치에 더 작은 상어가 있다면
                int small_shark = Map[sharks[i].r][sharks[i].c].second;
                sharks[small_shark].alive = false;

                Map[sharks[i].r][sharks[i].c].first = sharks[i].size;
                Map[sharks[i].r][sharks[i].c].second = sharks[i].index;
            }
        }
    }
}

void MoveAndHunt(int kingLocation) {
    int top = 987654321;
    for (int i = 0; i < sharks.size(); i++) {
        if (sharks[i].c == kingLocation && sharks[i].alive) { // 낚시왕 열에 있는 가장 가까운 상어를 찾음
            top = min(top, sharks[i].r);
        }
    }

    if (top != 987654321) { // 낚시왕 열에 있는 가장 가까운 상어를 사냥
        int shark = Map[top][kingLocation].second;
        result += sharks[shark].size;
        sharks[shark].alive = false;
        Map[top][kingLocation].first = -1;
        Map[top][kingLocation].second = -1;
    }

    // 상어 이동
    MoveSharks();
}

int main() {

    cin >> R >> C >> M;

    Init();

    for (int i = 0; i < M; i++) {
        int r, c, s, d, z;
        cin >> r >> c >> s >> d >> z;
        if (d == 1 || d == 2) // 시간초과 해결방법!!!
            s %= ((R - 1) * 2);
        if (d == 3 || d == 4)
            s %= ((C - 1) * 2);
        sharks.push_back({r, c, s, d, z, i, true});
        Map[r][c] = make_pair(z, i); // 하나의 칸에 둘 이상의 상어가 있는 경우는 없다.
    }

    for (int i = 1; i <= C; i++) { // 1초마다 1칸씩 C열까지 이동
        // Debugg();
        MoveAndHunt(i);
        // Debugg();
    }

    cout << result;
    return 0;
}