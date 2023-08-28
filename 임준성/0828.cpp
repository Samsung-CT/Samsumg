#include<iostream>
#include<memory.h>

using namespace std;

int dr[4] = { 0,1,0, -1 };
int dc[4] = { 1,0, -1,0 };

int N;
int board[20][20];

void rotate() {//시계방향 90도 회전
	int cpy_board[20][20];
	memcpy(cpy_board, board, sizeof(board));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			board[i][j] = cpy_board[N - 1 - j][i];
		}
	}
}

int max_val = 0;
void dfs(int count) {
	if (count == 5) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (max_val < board[i][j]) {
					max_val = board[i][j];
				}
			}
		}
		return;
	}

	int cpy_board[20][20];
	for (int i = 0; i < 4; i++) {
		memcpy(cpy_board, board, sizeof(board));
		for (int r = 0; r < N; r++) {
			int pos = 0;
			int val = -1;
			for (int c = 0; c < N; c++) {
				if (val == -1 && board[r][c] > 0) {
					val = board[r][c];
					board[r][c] = 0;
					continue;
				}

				if (board[r][c] != 0) {
					if (val == board[r][c]) {
						board[r][pos++] = val * 2;
						val = -1;
					}
					else {
						board[r][pos++] = val;
						val = board[r][c];
					}
					board[r][c] = 0;
				}
			}
			if (val > 0) {
				board[r][pos] = val;
			}
		}

		dfs(count + 1);
		memcpy(board, cpy_board, sizeof(board));
		rotate();
	}
}

int main() {
	
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> board[i][j];
		}
	}

	dfs(0);

	cout << max_val;

	return 0;
}
