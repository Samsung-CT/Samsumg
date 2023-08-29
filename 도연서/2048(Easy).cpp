//2048(Easy)
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;

int n;
int map[21][21];
int cmap[21][21];
int direction[6];
vector<int> v;
queue<int> q;

void clearq() {
    while(!q.empty()) {
        q.pop();
    }
}

void copy() {
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=n;j++) {
            cmap[i][j] = map[i][j];
        }
    }
}

void left() {
    clearq();

    for(int i=1;i<=n; i++) {
        for(int j=1;j<=n; j++) {
            if(cmap[i][j] == 0) continue;
            q.push(cmap[i][j]);
        }

        for(int j=1;j<=n;j++) {
            if(!q.empty() && q.front() != 0) {
                cmap[i][j] = q.front();
                q.pop();
            } else {
                cmap[i][j] = 0;
            }
        }
    }

    for(int i=1;i<=n;i++) {
        for(int j=1;j<n;j++) {
            if(cmap[i][j] == cmap[i][j+1]) {
                cmap[i][j] *= 2;
                cmap[i][j+1] = 0;
            }
        }
    }

    clearq();

    for(int i=1;i<=n;i++) {
        for(int j=1;j<=n;j++) {
            if(cmap[i][j] == 0) continue;
            q.push(cmap[i][j]);
        }

        for(int j=1;j<=n;j++) {
            if(!q.empty() && q.front() != 0) {
                cmap[i][j] = q.front();
                q.pop();
            } else {
                cmap[i][j] = 0;
            }
        }
    }
}

void right() {
    clearq();

    for(int i=1;i<=n; i++) {
        for(int j=n;j>=1; j--) {
            if(cmap[i][j] == 0) continue;
            q.push(cmap[i][j]);
        }

        for(int j=n;j>=1;j--) {
            if(!q.empty() && q.front() != 0) {
                cmap[i][j] = q.front();
                q.pop();
            } else {
                cmap[i][j] = 0;
            }
        }
    }

    for(int i=1;i<=n;i++) {
        for(int j=n;j>1;j--) {
            if(cmap[i][j-1] == cmap[i][j]) {
                cmap[i][j] *= 2;
                cmap[i][j-1] = 0;
            }
        }
    }
    clearq();

    for(int i=1;i<=n;i++) {
        for(int j=n;j>=1;j--) {
            if(cmap[i][j] == 0) continue;
            q.push(cmap[i][j]);
        }

        for(int j=n;j>=1;j--) {
            if(!q.empty() && q.front() != 0) {
                cmap[i][j] = q.front();
                q.pop();
            } else {
                cmap[i][j] = 0;
            }
        }
    }
}

void up() {
    clearq();

    for(int j=1;j<=n; j++) {
        for(int i=1;i<=n; i++) {
            if(cmap[i][j] == 0) continue;
            q.push(cmap[i][j]);
        }

        for(int i=1;i<=n;i++) {
            if(!q.empty() && q.front() != 0) {
                cmap[i][j] = q.front();
                q.pop();
            } else {
                cmap[i][j] = 0;
            }
        }
    }

    for(int j=1;j<=n; j++) {
        for(int i=1;i<n; i++) {
            if(cmap[i][j] == cmap[i+1][j]) {
                cmap[i][j] *= 2;
                cmap[i+1][j] = 0;
            }
        }
    }

    clearq();

    for(int j=1;j<=n; j++) {
        for(int i=1;i<=n; i++) {
            if(cmap[i][j] == 0) continue;
            q.push(cmap[i][j]);
        }

        for(int i=1;i<=n; i++) {
            if(!q.empty() && q.front() != 0) {
                cmap[i][j] = q.front();
                q.pop();
            } else {
                cmap[i][j] = 0;
            }
        }
    }
}

void down() {
    clearq();

    for(int j=1;j<=n; j++) {
        for(int i=n;i>=1; i--) {
            if(cmap[i][j] == 0) continue;
            q.push(cmap[i][j]);
        }

        for(int i=n;i>=1; i--) {
            if(!q.empty() && q.front() != 0) {
                cmap[i][j] = q.front();
                q.pop();
            } else {
                cmap[i][j] = 0;
            }
        }
    }

    for(int j=1;j<=n; j++) {
        for(int i=n;i>1; i--) {
            if(cmap[i][j] == cmap[i-1][j]) {
                cmap[i][j] *= 2;
                cmap[i-1][j] = 0;
            }
        }
    }

    clearq();

    for(int j=1;j<=n; j++) {
        for(int i=n;i>=1; i--) {
            if(cmap[i][j] == 0) continue;
            q.push(cmap[i][j]);
        }

        for(int i=n;i>=1; i--) {
            if(!q.empty() && q.front() != 0) {
                cmap[i][j] = q.front();
                q.pop();
            } else {
                cmap[i][j] = 0;
            }
        }
    }
}

void findMax() {
    int maxx = -1;
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=n;j++) {
            maxx = max(maxx,cmap[i][j]);
        }
    }

    v.push_back(maxx);
}

void selectDirection(int k, int cnt) {
    if(cnt == 5) {
        memset(cmap,0,sizeof(cmap));
        copy();

        for(int i=0;i<5;i++) {
            if(direction[i] == 0) { right(); }
            else if(direction[i] == 1) { left(); }
            else if(direction[i] == 2) { down(); }
            else if(direction[i] == 3) { up(); }
        }
        findMax();
        return;
    } else {
        for(int idx=0;idx<4;idx++) {
            direction[cnt] = idx;
            selectDirection(idx,cnt+1);
        }
    }
}

int main() {
    cin >> n;
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=n;j++) {
            cin >> map[i][j];
        }
    }

    selectDirection(0,0);
    sort(v.begin(),v.end());

    cout << v[v.size()-1];

    return 0;
}
