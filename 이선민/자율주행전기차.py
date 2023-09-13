import sys
from collections import deque

input = sys.stdin.readline

n, m, c = map(int, input().replace("\n", "").strip().split(" "))
board = []
for _ in range(n):
    board.append(list(map(int, input().replace("\n", "").strip().split(" "))))
texi = list(map(int, input().replace("\n", "").strip().split(" ")))
guests_pos = {}
for _ in range(m):
    xs, ys, xe, ye = map(int, input().replace("\n", "").strip().split(" "))
    guests_pos[(xs-1, ys-1)] = (xe-1, ye-1)

def findNearGuest(board, guests_pos, texi):
    q = deque()
    q.append([texi[0], texi[1], 0])
    guestList = guests_pos.keys()
    dr = [-1, 0, 0, 1]
    dc = [0, -1, 1, 0]
    visit = [[False]*n for _ in range(n)]
    result = [(n,n), n*n]
    while q:
        r, c, dis = q.popleft()
        if (r,c) in guestList:
            if dis < result[1]:
                result = [(r,c), dis]
            if dis == result[1] and result[0][0] > r:
                result = [(r,c), dis]
            if dis == result[1] and result[0][0] == r and result[0][1] > c:
                result = [(r,c), dis]
        if visit[r][c]:
            continue
        visit[r][c] = True
        for i in range(4):
            nr = r+dr[i]
            nc = c+dc[i]
            if nr < 0 or nr >= n:
                continue
            if nc < 0 or nc >= n:
                continue
            if board[nr][nc] == 1:
                continue
            q.append([nr, nc, dis+1])
    if result[1] == n*n:
        return [(-1,-1), -1]
    return result

def goToDest(board, texi, end):
    q = deque()
    q.append([texi[0], texi[1], 0])
    visit = [[False]*n for _ in range(n)]
    dr = [-1, 0, 0, 1]
    dc = [0, -1, 1, 0]
    while q:
        r, c, dis = q.popleft()
        if (r,c) == end:
            return dis
        if visit[r][c]:
            continue
        visit[r][c] = True
        for i in range(4):
            nr = r+dr[i]
            nc = c+dc[i]
            if nr < 0 or nr >= n:
                continue
            if nc < 0 or nc >= n:
                continue
            if board[nr][nc] == 1:
                continue
            q.append([nr, nc, dis+1])
    return -1

def solution(texi, c):
    while guests_pos:
        # 승객 탑승 위치, 탑승위치까지 거리
        start, disToStart = findNearGuest(board, guests_pos, texi)
        # 승객이 있지만 승객에게 갈 수 없는 경우 예외처리
        if disToStart == -1:
            return -1
        # 출발지로 이동한만큼 배터리 소모
        c -= disToStart
        if c <= 0:
            return -1
        # 택시 위치 갱신
        texi = [start[0], start[1]]
        # 목적지로 이동
        disToEnd = goToDest(board, texi, guests_pos[start])
        # 목적지로 갈 수 없는 경우
        if disToEnd == -1:
            return -1
        # 목적지로 이동한만큼 배터리 소모
        c -= disToEnd
        if c < 0:
            return -1
        # 택시 위치 갱신
        texi = [guests_pos[start][0], guests_pos[start][1]]
        # 배터리 두배 충전
        c += disToEnd * 2
        # 태워준 승객 삭제
        del guests_pos[start]
    if c < 0:
        return -1
    return c


print(solution([texi[0]-1, texi[1] -1], c))