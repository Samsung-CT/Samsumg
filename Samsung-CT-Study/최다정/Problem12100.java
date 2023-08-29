
import java.io.*;
import java.util.*;

public class Problem12100 {

	static int N;
	static int[][] map;
	static int[][] tmap;
	static int[] direct = new int[5];
	static boolean[][] visited;
	static int[][] dir = { { -1, 0 }, { 1, 0 }, { 0, 1 }, { 0, -1 } }; // 상 하 우 좌
	static int max = Integer.MIN_VALUE;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer str;

		N = Integer.parseInt(br.readLine());

		map = new int[N][N];

		for (int i = 0; i < N; i++) {
			str = new StringTokenizer(br.readLine(), " ");
			for (int j = 0; j < N; j++) {
				map[i][j] = Integer.parseInt(str.nextToken());
			}
		}

		dfs(0, 5);
		System.out.println(max);
	}

	static void dfs(int index, int end) {
		if (end == index) {
			confirm();
		} else {
			for (int i = 0; i < 4; i++) {
				direct[index] = i;
				dfs(index + 1, end);
			}
		}
	}

	static void confirm() {
		tmap = new int[N][N];

		for (int i = 0; i < N; i++) {
			tmap[i] = map[i].clone();
		}

		for (int d = 0; d < 5; d++) {
			visited = new boolean[N][N];

			int dt = direct[d];

			if (dt == 0) { // 상
				for (int i = 0; i < N; i++) {
					for (int j = 0; j < N; j++) {
						if (tmap[i][j] != 0) {
							movingFunc(i, j, dt);
						}
					}
				}
			} else if (dt == 1) { // 하
				for (int i = N - 1; i >= 0; i--) {
					for (int j = 0; j < N; j++) {
						if (tmap[i][j] != 0) {
							movingFunc(i, j, dt);
						}
					}
				}
			} else if (dt == 2) { // 우
				for (int i = N - 1; i >= 0; i--) {
					for (int j = 0; j < N; j++) {
						if (tmap[j][i] != 0) {
							movingFunc(j, i, dt);
						}
					}
				}
			} else if (dt == 3) { // 좌
				for (int i = 0; i < N; i++) {
					for (int j = 0; j < N; j++) {
						if (tmap[j][i] != 0) {
							movingFunc(j, i, dt);
						}
					}
				}
			}
		}

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (tmap[i][j] > max) {
					max = tmap[i][j];
				}
			}
		}
	}

	static void movingFunc(int x, int y, int d) {

		while (true) {
			int nx = x + dir[d][0];
			int ny = y + dir[d][1];

			if (nx < 0 || nx >= N || ny < 0 || ny >= N) {
				return;
			}

			if (visited[nx][ny]) {
				return;
			}

			if (tmap[nx][ny] == tmap[x][y]) {
				visited[nx][ny] = true;
				tmap[nx][ny] = tmap[nx][ny] * 2;
				tmap[x][y] = 0;
				return;
			} else if (tmap[nx][ny] != 0) {
				return;
			}

			tmap[nx][ny] = tmap[x][y];
			tmap[x][y] = 0;
			x = nx;
			y = ny;
		}

	}

}
