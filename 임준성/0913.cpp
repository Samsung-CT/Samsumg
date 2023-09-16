#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int N,M;
vector<vector<int>> road(50, vector<int>(50,0));
vector<vector<int>> visit(50, vector<int>(50,0));

//북 동 남 서
int dr[4] = {-1,0,1,0};
int dc[4] = {0,1,0,-1};
struct car{
    int r;
    int c;
    int d;
};
car car_pos;

int ans = 1;

bool in_range(int r, int c){
    return 1<=r && r<=N-2 && 1<=c && c<=M-2;
}

bool chk_road(int r, int c){
    return in_range(r,c) && road[r][c] != 1 && visit[r][c] == 0;
}

bool chk_back(int r, int c){
    return in_range(r,c) && road[r][c] != 1;
}

void drive(){
    while(1){
        int nr, nc, nd;
        for(int i=1; i<=4; i++){
            nd = (car_pos.d + 4 - i) % 4;
            nr = car_pos.r + dr[nd];
            nc = car_pos.c + dc[nd];

            if(chk_road(nr,nc)){
                visit[nr][nc] = 1;
                ans++;
                car_pos = {nr,nc,nd};
                break;
            }
            if(i == 4){
                nd = (car_pos.d + 2) % 4;
                nr = car_pos.r + dr[nd];
                nc = car_pos.c + dc[nd];
                if(chk_back(nr,nc)){
                    if(visit[nr][nc] == 0){
                        visit[nr][nc] = 1;
                    }
                    car_pos = {nr,nc,car_pos.d};
                }
                else{
                    return;
                }
            }
        }
    }
}

int main() {
    cin >> N >> M;

    cin >> car_pos.r >> car_pos.c >> car_pos.d;
    visit[car_pos.r][car_pos.c] = 1;
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            cin >> road[i][j];
        }
    }

    drive();

    cout << ans;

    return 0;
}
