import sys
from collections import deque
from collections import deque
import sys
sys.stdin = open("input.txt","r")

from collections import deque
import math

# import sys
# sys.stdin = open('input.txt', 'r')

N, M, K = map(int, input().split())
arr2 = [list(map(int, input().split())) for _ in range(N)]
wall_list = [list(map(int, input().split())) for _ in range(M)]

# 필요한 변수
answer = 0
air = []
office = []
wall = [[[0] * 4 for _ in range(N)] for _ in range(N)]
cool = [[0] * N for _ in range(N)]


for r in range(N):
    for c in range(N):
        if arr2[r][c] == 1:
            office.append((r, c))
        elif arr2[r][c] > 1:
            air.append((r, c, arr2[r][c] - 2))

# 벽 처리
for r, c, d in wall_list:
    r -= 1
    c -= 1
    if d == 0:

        wall[r][c][1] = wall[r-1][c][3] = 1
    else:

        wall[r][c][0] = wall[r][c-1][2] = 1

# 델타 (좌-상-우-하)
dr = [0, -1, 0, 1]
dc = [-1, 0, 1, 0]







def is_finish():
    for x, y in office:
        if cool[x][y] < K:
            return False
    return True



def is_possible(row, col, d):
    if not (0 <= row < N and 0 <= col < N):
        return False
    if wall[row][col][d]:
        return False
    return True



def check(row, col, air_d):
    p1 = [False, row+dr[air_d], col+dc[air_d]]
    p2 = [False, -1, -1]
    p3 = [False, -1, -1]


    if not wall[row][col][air_d] and 0 <= p1[1] < N and 0 <= p1[2] < N:
        p1[0] = True

    sub_d = (air_d+2) % 4
    if air_d == 0:
        if not wall[row][col][1] and is_possible(row-1, col-1, sub_d):
            p2 = [True, row-1, col-1]
        if not wall[row][col][3] and is_possible(row+1, col-1, sub_d):
            p3 = [True, row+1, col-1]
    elif air_d == 1:
        if not wall[row][col][0] and is_possible(row-1, col-1, sub_d):
            p2 = [True, row-1, col-1]
        if not wall[row][col][2] and is_possible(row-1, col+1, sub_d):
            p3 = [True, row-1, col+1]
    elif air_d == 2:
        if not wall[row][col][1] and is_possible(row-1, col+1, sub_d):
            p2 = [True, row-1, col+1]
        if not wall[row][col][3] and is_possible(row+1, col+1, sub_d):
            p3 = [True, row+1, col+1]
    elif air_d == 3:
        if not wall[row][col][0] and is_possible(row+1, col-1, sub_d):
            p2 = [True, row+1, col-1]
        if not wall[row][col][2] and is_possible(row+1, col+1, sub_d):
            p3 = [True, row+1, col+1]

    return [p1, p2, p3]


# 1. 모든 에어컨에서 바람이 나온다.(끝판왕)
def wind():
    plus = [[0] * N for _ in range(N)]
    for ar, ac, ad in air:

        q = deque([(ar+dr[ad], ac+dc[ad], 5)])

        while q:
            r, c, v = q.popleft()

            plus[r][c] += v
            pos = check(r, c, ad)

            if v > 1:
                for p in pos:
                    if p[0] and (p[1], p[2], v-1) not in q:
                        q.append((p[1], p[2], v-1))
    for r in range(N):
        for c in range(N):
            cool[r][c] += plus[r][c]

# 2. 시원함이 '동시에' 섞인다.
def mix():
    res = [[0] * N for _ in range(N)]
    visited = [[0] * N for _ in range(N)]

    for r in range(N):
        for c in range(N):
            v = cool[r][c]

            for d in range(4):
                nr, nc = r + dr[d], c + dc[d]
                if not (0 <= nr < N and 0 <= nc < N):
                    continue
                if visited[nr][nc]:
                    continue
                if wall[r][c][d]:
                    continue
                nv = cool[nr][nc]
                diff = math.ceil(abs(v - nv) // 4)
                if nv > v:
                    res[nr][nc] -= diff
                    res[r][c] += diff
                else:
                    res[nr][nc] += diff
                    res[r][c] -= diff

            visited[r][c] = 1

    for r in range(N):
        for c in range(N):
            cool[r][c] += res[r][c]


def edge():
    for c in range(N):
        cool[0][c] = max(cool[0][c] - 1,0)
        cool[N-1][c] = max(cool[N-1][c] - 1,0)
    for r in range(1, N-1):
        cool[r][0] =  max(cool[r][0] - 1,0 )
        cool[r][N-1] = max(cool[r][N-1] - 1,0)






def solution():
    global answer
    # # 종료 조건 => 모든 사무실의 시원함이 k 이상 OR 분이 100이 넘어감.
    while not is_finish():
    # for i in range(1):
        if answer >= 100:
            print(-1)
            return
        # 1. 모든 에어컨에서 바람이 나온다.
        wind()
1
        # 2. 시원함이 섞인다.
        mix()
        # print_cool()
        # 3. 외벽 칸의 시원함이 1씩 감소한다.
        edge()
        # print_cool()
        answer += 1
    print(answer)


solution()
