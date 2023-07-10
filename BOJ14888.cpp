#include <iostream>
using namespace std;

int N;
int numbers[101];
int operators[4];

int max_num = -1000000000;
int min_num = 1000000000;

void Solve(int index, int total) {
    if (index == N) {
        if (total > max_num) {
            max_num = total;
        }
        if (total < min_num) {
            min_num = total;
        }
        return;
    }

    for (int i = 0; i < 4; i++) {
        if (operators[i] > 0) {
            operators[i]--;
            if (i == 0) {
                Solve(index + 1, total + numbers[index]);
            } else if (i == 1) {
                Solve(index + 1, total - numbers[index]);
            } else if (i == 2) {
                Solve(index + 1, total * numbers[index]);
            } else {
                Solve(index + 1, total / numbers[index]);
            }
            operators[i]++;
        }
    }

    return;
}

int main() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> numbers[i];
    }
    for (int i = 0; i < 4; i++) {
        cin >> operators[i];
    }

    Solve(1, numbers[0]);

    cout << max_num << '\n';
    cout << min_num;
}