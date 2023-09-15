#include <iostream>
#include <cmath>
#include <map>
#include <vector>
#include <queue>

using namespace std;

int N, M, K;
vector<vector<int>> board(20, vector<int>(20));
vector<vector<int>> walls(20, vector<int>(20));//1 위 2 왼 3 둘다

struct point{
    int r;
    int c;
};
vector<point> office;
vector<pair<point, int>> air_con;

//좌 위 오 아래
int dr[4] ={0,-1,0,1};
int dc[4] ={-1,0,1,0};

void pb(){
    cout << "------------ print board -------------\n";
    for(int x=0; x<N; x++){
        for(int y=0; y<N; y++){
            cout << board[x][y] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

void pw(){
    cout << "------------ print wall -------------\n";
    for(int x=0; x<N; x++){
        for(int y=0; y<N; y++){
            cout << walls[x][y] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

bool in_range(int r, int c){
    return 0 <= r && r <= N-1 && 0 <= c && c <= N-1;
}

bool dir1(int r, int c, int d){
    switch(d){
        //좌
        case 0:
            if(walls[r][c] == 2 || walls[r][c] == 3){
                return false;
            }
            break;
        //상
        case 1:
            if(walls[r][c] == 1 || walls[r][c] == 3){
                return false;
            }
            break;
        //우
        case 2:
            if(!in_range(r,c+1)){
                return false;
            }

            if(walls[r][c+1] == 2 || walls[r][c+1] == 3){
                return false;
            }
            break;
        //하
        case 3:
            if(!in_range(r+1,c)){
                return false;
            }

            if(walls[r+1][c] == 1 || walls[r+1][c] == 3){
                return false;
            }
            break;
    }

    return true;
}

bool dir2(int r, int c, int d){
    if(!in_range(r+dr[(d+1)%4], c+dc[(d+1)%4])){
        return false;
    }
    int nr = r+dr[(d+1)%4];
    int nc = c+dc[(d+1)%4];
    switch(d){
        //좌
        case 0:
            if(!dir1(r,c,1) || !dir1(nr,nc,d)){
                return false;
            }
            break;
        //상
        case 1:
            if(!dir1(r,c,2)  || !dir1(nr,nc,d)){
                return false;
            }
            break;
        //우
        case 2:
            if(!dir1(r,c,3) || !dir1(nr,nc,d)){
                return false;
            }
            break;
        //하
        case 3:
            if(!dir1(r,c,0) || !dir1(nr,nc,d)){
                return false;
            }
            break;
    }

    return true;
}

bool dir3(int r, int c, int d){
    if(!in_range(r+dr[(d+3)%4], c+dc[(d+3)%4])){
        return false;
    }
    int nr = r+dr[(d+3)%4];
    int nc = c+dc[(d+3)%4];
    switch(d){
        //좌
        case 0:
            if(!dir1(r,c,3) || !dir1(nr,nc,d)){
                return false;
            }
            break;
        //상
        case 1:
            if(!dir1(r,c,0)  || !dir1(nr,nc,d)){
                return false;
            }
            break;
        //우
        case 2:
            if(!dir1(r,c,1) || !dir1(nr,nc,d)){
                return false;
            }
            break;
        //하
        case 3:
            if(!dir1(r,c,2) || !dir1(nr,nc,d)){
                return false;
            }
            break;
    }

    return true;
}

void cooling(){
    for(int i=0; i<air_con.size(); i++){
        vector<vector<int>> temp(N, vector<int>(N));

        queue<pair<point,int>> q;
        int d = air_con[i].second;
        q.push({{air_con[i].first.r + dr[d], air_con[i].first.c + dc[d]}, 5});
        while(!q.empty()){
            int r = q.front().first.r;
            int c = q.front().first.c;
            int v = q.front().second;
            q.pop();
            temp[r][c] = v;
            if(v == 1){
                continue;
            }

            if(dir1(r,c,d) && in_range(r+dr[d], c+dc[d]) && temp[r+dr[d]][c+dc[d]] == 0){
                q.push({{r+dr[d], c+dc[d]}, v-1});
            }

            if(dir2(r,c,d) && in_range(r+dr[d]+dr[(d+1)%4], c+dc[d]+dc[(d+1)%4]) 
                && temp[r+dr[d]+dr[(d+1)%4]][c+dc[d]+dc[(d+1)%4]] == 0){
                q.push({{r+dr[d]+dr[(d+1)%4], c+dc[d]+dc[(d+1)%4]}, v-1});
            }

            if(dir3(r,c,d) && in_range(r+dr[d]+dr[(d+3)%4], c+dc[d]+dc[(d+3)%4]) 
                && temp[r+dr[d]+dr[(d+3)%4]][c+dc[d]+dc[(d+3)%4]] == 0){
                q.push({{r+dr[d]+dr[(d+3)%4], c+dc[d]+dc[(d+3)%4]}, v-1});
            }
        }

        for(int x=0; x<N; x++){
            for(int y=0; y<N; y++){
                board[x][y] += temp[x][y];
            }
        }
    }
}

void mix(){
    vector<vector<int>> temp(N, vector<int>(N));
    for(int x=0; x<N; x++){
        for(int y=0; y<N; y++){
            for(int i=0; i<2; i++){
                if(in_range(x+dr[i], y+dc[i]) && dir1(x,y,i)){
                    int v = floor(abs(board[x][y] - board[x+dr[i]][y+dc[i]]) / 4.0);
                    if(board[x][y] > board[x+dr[i]][y+dc[i]]){
                        temp[x][y] -= v;
                        temp[x+dr[i]][y+dc[i]] += v;
                    }
                    else if(board[x][y] < board[x+dr[i]][y+dc[i]]){
                        temp[x][y] += v;
                        temp[x+dr[i]][y+dc[i]] -= v;
                    }
                }
            }
            
        }
    }

    for(int x=0; x<N; x++){
        for(int y=0; y<N; y++){
            board[x][y] += temp[x][y];
        }
    }
}

void cooldown(){
    for(int i=0; i<N; i++){
        for(int j = 0; j<N; j++){
            if((i == 0 || j == 0 || i == N - 1 || j == N - 1) && board[i][j] > 0){
                board[i][j]--;
            }
        }
    }
}

bool chk(){
    for(int i=0; i<office.size(); i++){
        if(board[office[i].r][office[i].c] < K){
            return false;
        }
    }

    return true;
}

int main() {
    cin >> N >> M >> K;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            int temp;
            cin >> temp;
            if(temp == 1){
                office.push_back({i,j});
            }
            else if(temp > 0){
                air_con.push_back({{i,j}, temp-2});
            }
        }
    }

    for(int i=0; i<M; i++){
        int r, c, temp;
        cin >> r >> c >> temp;
        walls[r-1][c-1] += temp + 1;
    }

    int ans = 0;
    while(!chk()){
        cooling();
        mix();
        cooldown();
        ans++;
        if(ans > 100){
            ans = -1;
            break;
        }
    }
    
    cout << ans;

    return 0;
}
