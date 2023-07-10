#include <iostream>
#include <vector>
using namespace std;
bool map[101][101];
int x, y, d, g, cnt;
int end_x, end_y;             // 끝점의 정보
vector<int> dragon_direction; // 드래곤 커브 방향
int dx[4] = {0, -1, 0, 1};
int dy[4] = {1, 0, -1, 0};

void makeDragonCurve() {
    int size = dragon_direction.size() - 1;
    for (int i = size; i >= 0; i--) {
        int dir = (dragon_direction[i] + 1) % 4;

        end_x += dx[dir];
        end_y += dy[dir];

        // cout << end_x << " " << end_y << '\n';

        map[end_x][end_y] = true;
        dragon_direction.push_back(dir);
    }
}

int main() {
    cin >> cnt;
    for (int i = 0; i < cnt; i++) {
        cin >> y >> x >> d >> g;
        // 드래곤 커브의 스택 비우고 다시 시작
        dragon_direction.clear();
        // 시작점에 드래곤 커브 놓임
        map[x][y] = true;

        // 0세대는 먼저 만들어 놓음
        end_x = x + dx[d];
        end_y = y + dy[d];
        map[end_x][end_y] = true;
        dragon_direction.push_back(d);

        for (int j = 0; j < g; j++) {
            makeDragonCurve();
        }
    }

    int result = 0;
    // 100*100 2차원 행렬을 2중 for문 사용한 단순한 탐색
    // 인접한 4칸이 모두 true이면, 4칸이 모두 드래곤 커브의 일부인것
    // 갯수를 1증가시킨다.
    for (int i = 0; i <= 100; i++) {
        for (int j = 0; j <= 100; j++) {

            // 인접한 4칸의 정사각형이 모두 드래곤의 일부이면
            if (map[i][j] == true && map[i][j + 1] == true && map[i + 1][j] == true && map[i + 1][j + 1] == true) {

                // 갯수를 1 증가시킨다.
                result++;
            }
        }
    }

    cout << result;
}
