//2023/7/6
#include <string>
#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;

int n,m,k;
pair<int,vector<int>> tarr[11][11]; // 토지의 양분, 나무의 벡터
int arr[11][11]; //추가되는 양분의 양
int dy[] = { -1,-1,-1,0,1,1,1,0 }, dx[] = { -1,0,1,1,1,0,-1,-1 };

vector<pair<pair<int,int>,int>> dead = {make_pair(make_pair(0, 0), 0)}; //위치, 죽은나무 나이

void springAndSummer() {
    dead.clear(); dead.resize(0);

    for(int i=1;i<=n;i++) {
        for(int j=1;j<=n;j++) {
            if (tarr[i][j].second.size() == 0 ) continue;
            sort(tarr[i][j].second.begin(),tarr[i][j].second.end());
            for(int k=0;k<tarr[i][j].second.size();k++) {
                if(tarr[i][j].first < tarr[i][j].second[k]) { //토지의 양분이 나이보다 적을 때는 죽어야해
                    dead.push_back({{i,j},tarr[i][j].second[k]});
                    tarr[i][j].second.erase(tarr[i][j].second.begin()+k);
                    k--;
                } else {
                    tarr[i][j].first -= tarr[i][j].second[k];
                    tarr[i][j].second[k] += 1;
                }
            }
        }
    }

    for(int i=0;i<dead.size();i++){
        tarr[dead[i].first.first][dead[i].first.second].first += (dead[i].second/2);
    }

}

void fall() {
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=n;j++) {
            for(int l=0;l<tarr[i][j].second.size();l++){
                if (tarr[i][j].second[l] % 5 == 0) {
                    for(int k=0;k<8;k++) {
                        int nx = i + dx[k];
                        int ny = j + dy[k];
                        if (1 <= nx && nx <= n && 1 <= ny && ny <= n) {
                            tarr[nx][ny].second.push_back(1);
                        }
                    }
                }

            }
        }
    }
}

void winter() {
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=n;j++) {
            tarr[i][j].first += arr[i][j];
        }
    }
}

int main() {

    cin >> n >> m >> k;

    for(int i=1;i<=n;i++) {
        for(int j=1;j<=n;j++) {
            cin >> arr[i][j];
            tarr[i][j].first = 5; // 처음 모든칸 양분 5
        }
    }

    for(int i=0;i<m;i++) {
        int x,y,z;
        cin >> x >> y >> z;
        tarr[x][y].second.push_back(z);
    }

    for(int i=0;i<k;i++) {
        springAndSummer();
        fall();
        winter();
    }

    int cnt = 0;

    for(int i=1;i<=n;i++) {
        for(int j=1;j<=n;j++) {
            if(tarr[i][j].second.size() > 0) {
                cnt += tarr[i][j].second.size();
            }
        }
    }

    cout << cnt;

    return 0;

}
