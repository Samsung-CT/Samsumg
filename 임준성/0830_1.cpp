#include <string>
#include <vector>
using namespace std;

int N, M;

bool in_range(int r, int c){
    return r>=0 && r<N && c>=0 && c<M;
}

int solution(vector<vector<int>> board, vector<vector<int>> skill) {
    N = board.size();
    M = board[0].size();
    vector<vector<int>> v(N, vector<int>(M,0));
    
    for(int i=0; i<skill.size(); i++){
        int r1 = skill[i][1];
        int c1 = skill[i][2];
        int r2 = skill[i][3] + 1;
        int c2 = skill[i][4] + 1;
        int d = skill[i][5];
        if(skill[i][0] == 1){
            d *= -1;
        }
        
        v[r1][c1] += d;
        if(in_range(r1,c2)){
            v[r1][c2] -= d;
        }
        if(in_range(r2,c1)){
            v[r2][c1] -= d;
        }
        if(in_range(r2,c2)){
            v[r2][c2] += d;
        }
    }
    
    for(int i=1; i<N; i++){
        for(int j=0; j<M; j++){
            v[i][j] += v[i-1][j];
        }
    }
    for(int i=0; i<N; i++){
        for(int j=1; j<M; j++){
            v[i][j] += v[i][j-1];
        }
    }
    
    int ans = 0;
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            if(board[i][j] + v[i][j] > 0){
                ans++;
            }
        }
    }
    
    return ans;
}
