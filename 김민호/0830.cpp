#include <algorithm>
#include <string>
#include <vector>

using namespace std;
vector<int> parents(200);

int findParent(int child) {
    if (parents[child] == child)
        return child;

    return parents[child] = findParent(parents[child]);
}

void Union(int child1, int child2) {
    child1 = findParent(child1);
    child2 = findParent(child2);

    if (child1 < child2)
        parents[child2] = child1;
    else if (child1 > child2)
        parents[child1] = child2;
}

int solution(int n, vector<vector<int>> computers) {
    int answer = 0;

    for (int i = 0; i < n; i++) {
        parents[i] = i;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j)
                continue;

            if (computers[i][j] == 1) {
                Union(i, j);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        parents[i] = findParent(i);
    }

    sort(parents.begin(), parents.begin() + n);

    int temp = parents[0];
    answer++;

    for (int i = 1; i < n; i++) {
        if (parents[i] != temp) {
            answer++;
            temp = parents[i];
        }
    }

    return answer;
}