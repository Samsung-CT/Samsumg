#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int N, M, C;
int board[21][21];

int dr[4] = {0,-1,1,0};
int dc[4] = {-1,0,0,1};

struct point{
    int r;
    int c;
};

point car;
vector<point> p;

void pb(){
    cout << "-------- print board ----------\n";
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            cout << board[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

void pc(){
    cout << "-------- print car ----------\n";
    cout << car.r << " " << car.c << endl;;
}

bool in_range(int r, int c){
    return 1<=r && r<=N && 1<=c && c<=N;
}

point find_p(){
    if(board[car.r][car.c] > 1){
        return { 0, board[car.r][car.c] - 2};
    }

    int flag = 500;
    point np = {-1,-1};
    queue<point> q;
    int visit[21][21] = {0,};
    q.push({car.r, car.c});
    visit[car.r][car.c] = 1;
    while(!q.empty()){
        int r = q.front().r;
        int c = q.front().c;
        q.pop();
        for(int i=0; i<4; i++){
            if(!in_range(r+dr[i], c+dc[i])
                || visit[r+dr[i]][c+dc[i]] > 0
                || board[r+dr[i]][c+dc[i]] == 1){
                continue;
            }

            if(board[r+dr[i]][c+dc[i]] > 1){
                if(flag > visit[r][c]){
                    flag = visit[r][c];
                    np = {r+dr[i], c+dc[i]};
                }
                else if(flag == visit[r][c]){
                    if(np.r > r+dr[i]){
                        np = {r+dr[i], c+dc[i]};
                        continue;
                    }
                    
                    if(np.r == r+dr[i]){
                        if(np.c > c+dc[i]){
                            np = {r+dr[i], c+dc[i]};
                            continue;
                        }
                    }
                }
                continue;
            }

            if(C == visit[r][c] || flag <= visit[r][c]){
                continue;
            }

            q.push({r+dr[i], c+dc[i]});
            visit[r+dr[i]][c+dc[i]] = visit[r][c] + 1;
        }
    }

    if(flag == 500){
        return np;
    }

    car = np;
    return {flag, board[np.r][np.c] - 2};
}

int go(int num){
    queue<point> q;
    int visit[21][21] = {0,};
    q.push({car.r, car.c});
    visit[car.r][car.c] = 1;
    while(!q.empty()){
        int r = q.front().r;
        int c = q.front().c;
        q.pop();
        for(int i=0; i<4; i++){
            if(!in_range(r+dr[i], c+dc[i])
                || visit[r+dr[i]][c+dc[i]] > 0
                || board[r+dr[i]][c+dc[i]] == 1){
                continue;
            }

            if(r+dr[i] == p[num].r && c+dc[i] == p[num].c){
                car = {r+dr[i], c+dc[i]};
                return visit[r][c];
            }

            if(C == visit[r][c]){
                continue;
            }

            q.push({r+dr[i], c+dc[i]});
            visit[r+dr[i]][c+dc[i]] = visit[r][c] + 1;
        }
    }

    return -1;
}

void drive(){
    point a;// 손님거리, 사람번호
    int dis;// 목적지거리
    while( M>0 && C>0 ){
        a = find_p();
        if(a.r == -1 || (a.r > 0 && C-a.r <= 0)){
            break;
        }
        
        C -= a.r;
        board[car.r][car.c] = 0;

        //--------------------------------------------------
        // cout << "----- after find person -------\n\n";
        // cout << a.r << "\t" << a.c << "\t" << C << endl;
        // pb();
        // pc();

        dis = go(a.c);
        
        if(dis == -1){
            break;
        }
        C += dis;
        M--;
        //--------------------------------------------------
        // cout << "----- after find des -------\n\n";
        // cout << dis << "\t" << C << endl;
        // pb();
        // pc();
    }
}

void input(){
    cin >> N >> M >> C;
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            cin >> board[i][j];
        }
    }

    cin >> car.r >> car.c;

    int x1, y1, x2, y2;
    for(int i=0; i<M; i++){
        cin >> x1 >> y1 >> x2 >> y2;
        p.push_back({x2,y2});
        board[x1][y1] = i+2;
    }
}

int main() {
    input();
    drive();
    if(M>0){
        cout << -1;
    }
    else{
        cout << C;
    }
    return 0;
}
