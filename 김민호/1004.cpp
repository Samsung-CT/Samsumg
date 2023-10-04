#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

int N, M, D;
int map[16][16];
int result = 0;
vector<int> combination;
vector<pair<int, int>> enemies;

// 두 번째 int를 기준으로 오름차순 정렬하는 비교 함수
bool sortBySecondInt(const pair<int, int> &a, const pair<int, int> &b) { return a.second < b.second; }

int attackAndMove(int dead, vector<int> archers, vector<pair<int, int>> enemies_location) {
    vector<pair<int, int>> copied_enemies = enemies_location;
    sort(copied_enemies.begin(), copied_enemies.end(), sortBySecondInt); // 가장 왼쪽에 있는 적 공격하기 위해
    bool dead_enemies[400] = {
        false,
    };

    if (enemies_location.size() == 0) { // 모든 적이 제거되면
        return dead;
    } else { // 적이 존재하면 공격
        int min_dist = 987654321;
        int dead_enemy = -1;

        for (int i = 0; i < archers.size(); i++) { // i 번째 궁수와 가장 가까운 적 찾음
            for (int j = 0; j < copied_enemies.size(); j++) {
                int dist = abs(N - copied_enemies[j].first) + abs(archers[i] - copied_enemies[j].second);

                if (dist <= D && dist < min_dist) {
                    min_dist = dist;
                    dead_enemy = j; // dead_enemy : i 번째 궁수와 가장 가까운 적
                }
            }

            min_dist = 987654321;

            // i 번쨰 궁수와 가장 가까운 적 기록
            dead_enemies[dead_enemy] = true;
        }

        for (int i = 0; i < N * M; i++) {
            if (dead_enemies[i] == true) {
                copied_enemies[i].first = -1;
                copied_enemies[i].second = -1;
            }
        }

        vector<pair<int, int>> temp;
        for (int i = 0; i < copied_enemies.size(); i++) {
            if (copied_enemies[i].first == -1 && copied_enemies[i].second == -1) {
                dead++;
            } else {
                if (copied_enemies[i].first + 1 < N) {
                    temp.push_back({copied_enemies[i].first + 1, copied_enemies[i].second});
                }
            }
        }

        return attackAndMove(dead, archers, temp);
    }
}

void makeCombination(int start, int cnt) { // 궁수의 위치 -> 조합
    if (cnt == 3) {                        // 조합이 완성되면
        vector<int> archers = combination;
        vector<pair<int, int>> copied_enemies = enemies;
        result = max(result, attackAndMove(0, archers, copied_enemies)); // 공격, 이동 시작

        return;
    }

    for (int i = start; i < M; i++) {
        combination.push_back(i);
        makeCombination(i + 1, cnt + 1);
        combination.pop_back();
    }
}

int main() {
    cin >> N >> M >> D;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> map[i][j];
            if (map[i][j] == 1) {
                enemies.push_back({i, j});
            }
        }
    }

    makeCombination(0, 0);

    cout << result;

    return 0;
}