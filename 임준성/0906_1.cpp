#include <string>
#include <vector>
#include <iostream>
using namespace std;

int N;//화살 총 개수
int score = 0;// 점수 차
vector<int> answer;
vector<int> apeach;//어피치 정보
vector<int> temp;//라이언 정보(임시)
void dfs(int idx, int p, int l, int cnt){
    if(idx == 10){
        if(p < l && score <= l - p){
            temp[10] = N - cnt;
            
            if(score < l - p){
                score = l - p;
                answer = temp;
            }
            else{
                for(int i=10; i>=0; i--){
                    if(answer[i] < temp[i]){
                        answer = temp;
                        break;
                    }
                    else if(answer[i] > temp[i]){
                        break;
                    }
                }
            }
        }
        return;
    }
    
    if(N - cnt > apeach[idx]){
        temp[idx] = apeach[idx] + 1;
        dfs(idx+1, p, l+10-idx, cnt + apeach[idx] + 1);
        temp[idx] -= apeach[idx] + 1;
    }

    if(apeach[idx] > 0){
        dfs(idx+1, p+10-idx, l, cnt);
    }
    else{
        dfs(idx+1, p, l, cnt);
    }
    
}

vector<int> solution(int n, vector<int> info) {
    temp = vector<int>(11);
    answer = vector<int>(11);
    apeach = info;
    N = n;
    
    dfs(0,0,0,0);
    
    if(score == 0){
        return vector<int>(1,-1);
    }
    
    return answer;
}
