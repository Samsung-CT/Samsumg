import java.io.*;
import java.util.*;

public class Problem17822 {

	static int N, M, T;
	static int[][] arr; // 원판을 2차원배열로 표현

	static int[][] dir = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };
	static Queue<int[]> q = new LinkedList<>();
	static boolean[][] visited;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer str = new StringTokenizer(br.readLine(), " ");

		N = Integer.parseInt(str.nextToken());
		M = Integer.parseInt(str.nextToken());
		T = Integer.parseInt(str.nextToken());

		arr = new int[N + 1][M + 1];

		for (int i = 1; i < N + 1; i++) {
			str = new StringTokenizer(br.readLine());
			for (int j = 1; j < M + 1; j++) {
				arr[i][j] = Integer.parseInt(str.nextToken());
			}
		}

		while (T-- > 0) {
			str = new StringTokenizer(br.readLine(), " ");
			int x = Integer.parseInt(str.nextToken());
			int d = Integer.parseInt(str.nextToken());
			int k = Integer.parseInt(str.nextToken());

			rotateFunc(x, d, k);

			deleteFunc();

		}

		int result = 0;
		for (int i = 1; i < N + 1; i++) {
			for (int j = 1; j < M + 1; j++) {
				result += arr[i][j];
			}
		}
		System.out.println(result);
	}

	static void rotateFunc(int x, int d, int k) {

		for (int i = 1; i < N + 1; i++) {

			if (i % x != 0) {
				continue;
			}

			// 회전을 위한 임시 배열 생성
			int[] temp = new int[M + 1];

			// 임시 배열 세팅
			for (int j = 1; j < M + 1; j++) {
				temp[j] = arr[i][j];
			}

			int ind = k;
			while (ind-- > 0) {

				// 시계 방향 회전
				if (d == 0) {
					for (int j = 2; j < M + 2; j++) {
						if (j == M + 1) {
							temp[1] = arr[i][j - 1];
							continue;
						}

						temp[j] = arr[i][j - 1];
					}
				}

				// 반시계 방향 회전
				if (d == 1) {
					for (int j = 1; j < M + 1; j++) {
						if (j == M) {
							temp[j] = arr[i][1];
							continue;
						}
						temp[j] = arr[i][j + 1];

					}
				}

				for (int j = 1; j < M + 1; j++) {
					arr[i][j] = temp[j];
				}

			}

		}

	}

	static void deleteFunc() {
		boolean[][] check = new boolean[N + 1][M + 1];
		int cnt = 0;
		int sum = 0;
		int scnt = 0;

		int[][] before = new int[N + 1][M + 1];
		for (int i = 1; i < N + 1; i++) {
			for (int j = 1; j < M + 1; j++) {
				sum += arr[i][j]; // 평균을 구하기 위한 총합
				if (arr[i][j] > 0)
					scnt++; // 평균을 구하기 위한 개수
				before[i][j] = arr[i][j];

				for (int k = 0; k < 4; k++) {
					int nx = i + dir[k][0];
					int ny = j + dir[k][1];

					if (nx <= 0 || ny <= 0 || nx > N || ny > M) {
						continue;
					}

					if (arr[i][j] != arr[nx][ny]) {
						continue;
					}

					if (arr[i][j] == arr[nx][ny]) {
						check[i][j] = true;
						check[nx][ny] = true;
					}
				}

				if (j == M) {
					if (arr[i][j] == arr[i][1]) {
						check[i][j] = true;
						check[i][1] = true;
					}
				}

			}
		}

		for (int i = 1; i < N + 1; i++) {
			for (int j = 1; j < M + 1; j++) {
				if (check[i][j]) {
					arr[i][j] = 0;
				}
				if (before[i][j] != arr[i][j]) {
					cnt++;
				}
			}
		}

		if (cnt < 1) {
			averageFunc(sum, scnt);
			return;
		}
	}

	static void averageFunc(int sum, int scnt) {
		double s = (double) sum;
		double c = (double) scnt;
		double avg = s / c;
		for (int i = 1; i < N + 1; i++) {
			for (int j = 1; j < M + 1; j++) {
				if (arr[i][j] == 0) {
					continue;
				}
				if (arr[i][j] == avg) {
					continue;
				}
				if (arr[i][j] > avg) {
					arr[i][j] -= 1;
					continue;
				}
				if (arr[i][j] < avg) {
					arr[i][j] += 1;
					continue;
				}
			}
		}
	}

}
