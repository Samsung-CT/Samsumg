#include <iostream>
using namespace std;
#define N 21 // Board Max = 20 + 하나 더 여유
int b[N][N], n, M = 5; // Board 초기 상태, Board size, Max move
int c[N][N]; // 가장 큰 블록의 값을 구하는 배열
int dfs[][2] = { {1, 0}, {0, -1}, {-1, 0}, {0, 1}};
int ans; // the biggest combine

void turn(){ // Board를 돌린다.

}

void move(){ // 이동

}

void combine(){ // 똑같은 수 2 -> 합치고, 3 -> 이동하려고 하는 쪽의 칸을 먼저 합친다

}

bool clash(){ // 충돌 여부 : 한 번 충돌 -> 합쳐짐 X

}

void input(){ // Board size, Board 초기 상태 입력
    cin >> n;
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            cin >> b[i][j];
        }
    }
}

void pro(){ // 2048 game
    while(M--){
        // 1. board를 돌리면, 숫자가 이동한다.
        turn();
        move();
        // 2. 충돌
        while(clash());
        // 3-1. 같은값 3개 -> 이동하려는 쪽의 칸이 먼저 합쳐진다.
        // 3-2. 같은값 2개 -> 하나로 합쳐진다.
        combine();
    }
    cout << ans;
}

int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    input();
    pro();
    return 0;
}