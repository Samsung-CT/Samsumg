import java.io.*;
import java.util.*;

public class Problem17143 {

	static int R, C, M;
	static int result = 0; // 잡은 상어의 크기의 합
	static int[][] sharkInfo;
	static int[][] map;
	static int[][] temp;
	static int[][] dir = { { 0, 0 }, { -1, 0 }, { 1, 0 }, { 0, 1 }, { 0, -1 } }; // 상 하 우 좌

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer str = new StringTokenizer(br.readLine());

		R = Integer.parseInt(str.nextToken()); // 행
		C = Integer.parseInt(str.nextToken()); // 열
		M = Integer.parseInt(str.nextToken());

		sharkInfo = new int[M + 1][3];
		map = new int[R + 1][C + 1];

		for (int i = 1; i < M + 1; i++) {
			str = new StringTokenizer(br.readLine());

			int x = Integer.parseInt(str.nextToken());
			int y = Integer.parseInt(str.nextToken());
			// i = 상어의 번호
			map[x][y] = i;

			for (int j = 0; j < 3; j++) {
				// 0 = s(속력)
				// 1 = d(이동 방향)
				// 2 = z(크기)
				sharkInfo[i][j] = Integer.parseInt(str.nextToken());
			}
		}

		int T = 0; // 어부의 위치
		while (T++ < C) {
			// 어부의 위치에 상어가 있는지 확인
			for (int i = 1; i <= R; i++) {
				if (map[i][T] != 0) {
					// 어부의 위치에 상어가 있는 경우
					int sharkNum = map[i][T];
					// 상어를 잡음
					map[i][T] = 0;
					// 잡은 상어의 크기를 더함
					result += sharkInfo[sharkNum][2];
					// 땅과 가장 가까운 상어를 잡으므로 다음 반복문 미진행
					i = R + 99;
				}

			}

			temp = new int[R + 1][C + 1];
			// 상어의 이동
			sharkFunc();
			// 새로 변경된 temp배열을 map에 밀어넣기
			for (int i = 1; i <= R; i++) {
				for (int j = 1; j <= C; j++) {
					map[i][j] = temp[i][j];
				}
			}
		}
		
		System.out.println(result);

	}

	// 상어의 이동
	static void sharkFunc() {
		for (int i = 1; i <= R; i++) {
			for (int j = 1; j <= C; j++) {
				if (map[i][j] != 0) {
					/**
					 * A B C D E F G H
					 * 1 2 3 4 5 6 7 8
					 */
					int sharkNum = map[i][j];
					int s = sharkInfo[sharkNum][0]; // 상어의 속도
					int d = sharkInfo[sharkNum][1]; // 상어의 방향

					moovingFunc(sharkNum, s, d, i, j);
				}
			}
		}
	}

	static void moovingFunc(int sn, int s, int d, int x, int y) {

		int nx = 0, ny = 0;
		if (s == 0) {
			nx = x; ny = y;
		} else {
			for (int i = 0; i < s; i++) {
				nx = x + dir[d][0];
				ny = y + dir[d][1];

				if (nx < 1 || ny < 1 || nx > R || ny > C) {
					if (d == 1)
						d = 2;
					else if (d == 2)
						d = 1;
					else if (d == 3)
						d = 4;
					else if (d == 4)
						d = 3;
					i--;
				} else {
					x = nx;
					y = ny;
				}
			}
		}
		
		sharkInfo[sn][1] = d;

		// 같은 칸에 상어가 두마리면 큰 상어만 남음
		if (temp[nx][ny] != 0 ) {
			int tn = temp[nx][ny];
			if (sharkInfo[tn][2] > sharkInfo[sn][2]) {
				//원래 있던 상어가 더 큰 경우
				temp[nx][ny] = temp[nx][ny];
			} else {
				//새로 온 상어가 더 큰 경우
				temp[nx][ny] = sn;
			}
		} else {
			temp[nx][ny] = sn;
		}
	}
}
