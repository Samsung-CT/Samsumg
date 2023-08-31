#include <string>
#include <vector>
#include <queue>

using namespace std;

int solution(int n, vector<vector<int>> computers) {
    int answer = 0;
    vector<bool> visit(n,false);
    for(int i=0; i<n; i++){
        if(visit[i]){
            continue;
        }
        
        answer++;
        queue<int> q;
        q.push(i);
        visit[i] = true;
        while(!q.empty()){
            int f = q.front();
            for(int j=0; j<n; j++){
                if(computers[f][j] == 0 || visit[j] || j==f){
                    continue;
                }
                
                visit[j] = true;
                q.push(j);
            }
            q.pop();
        }
    }
    return answer;
}
