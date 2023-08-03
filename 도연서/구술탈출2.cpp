//2023/7/19
#include <iostream>
#include <queue>
using namespace std;

int n,m;
char board[11][11];
int dx[] = { 1,-1,0,0 };
int dy[] = { 0,0,1,-1 };
bool visit[11][11][11][11];
pair<int,int> red,blue;

struct Info {
    int rx,ry;
    int bx,by;
    int cnt;
};

queue<Info> q;

int bfs(int rx, int ry, int bx, int by) {

    q.push({rx,ry,bx,by,0});
    visit[rx][ry][bx][by] = true;

    while(!q.empty()) {

        int currx = q.front().rx;
        int curry = q.front().ry;
        int curbx = q.front().bx;
        int curby = q.front().by;
        int curCount = q.front().cnt;

        q.pop();

        if (curCount > 10) break;

        if(board[currx][curry] == 'O' && board[curbx][curby] != 'O') {
            return curCount;
        }

        for(int i=0;i<4;i++) {
            int newrx = currx;
            int newry = curry;
            int newbx = curbx;
            int newby = curby;
            int cnt = curCount+1;
            int rc = 0,bc = 0;

            while(1) {
                if(board[newrx][newry] != '#' && board[newrx][newry] != 'O') {
                    newrx += dx[i]; newry += dy[i];
                    rc++;
                } else {
                    if(board[newrx][newry] == '#') {
                        newrx -= dx[i]; newry -= dy[i];
                    }
                    break;
                }
            }

            while(1) {
                if(board[newbx][newby] != '#' && board[newbx][newby] != 'O') {
                    newbx += dx[i]; newby += dy[i];
                    bc++;
                } else {
                    if(board[newbx][newby] == '#') {
                        newbx -= dx[i]; newby -= dy[i];
                    }
                    break;
                }
            }

            if(newrx == newbx && newry == newby) {
                if(board[newrx][newry] != 'O' && board[newbx][newby] != 'O' ) {
                    if(rc < bc) {
                        newbx -= dx[i]; newby -= dy[i];
                    } else {
                        newrx -= dx[i]; newry -= dy[i];
                    }
                }
            }

            if(visit[newrx][newry][newbx][newby]) continue;
            visit[newrx][newry][newbx][newby] = true;
            q.push({newrx,newry,newbx,newby,cnt});

        }

    }

    return -1;
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    cin >> n >> m;

    for(int i=0;i<n;i++) {
        for(int j=0;j<m;j++) {
            cin >> board[i][j];
            if(board[i][j] == 'R') {
                red.first = i;
                red.second = j;
            } else if (board[i][j] == 'B') {
                blue.first = i;
                blue.second = j;
            }
        }
    }

    cout << bfs(red.first,red.second,blue.first,blue.second);

    return 0;

}
