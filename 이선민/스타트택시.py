import sys
from collections import deque
input = sys.stdin.readline

N, M, fuel = map(int, input().split(" "))
board = []
for _ in range(N):
    board.append(list(map(int, input().split(" "))))

taxi = list(map(int, input().split(" ")))
pList = [] # 승객 탑승 위치
for i in range(M):
    sr, sc, er, ec = map(int, input().split(" "))
    pList.append(((sr-1,sc-1),(er-1,ec-1)))

def checkPosition(result, r,c, f):
    if result == -1:
        return True
    if f < result[2]:
        return True
    if f == result[2] and r < result[0][0]:
        return True
    if f == result[2] and r == result[0][0] and c < result[0][1]:
        return True
    return False

def getIdx(pList, start):
    for idx, item in enumerate(pList):
        if item[0] == start:
            return idx
    return -1

def findCloseGuest(board, taxi, pList):
    q = deque()
    visit = [[False] * N for _ in range(N)]
    dr = [-1, 0, 0, 1]
    dc = [0, -1, 1, 0]
    q.append([taxi[0], taxi[1], 0])
    result = -1
    target = -1
    while q:
        r, c, f = q.popleft()
        if visit[r][c]: continue
        visit[r][c] = True
        idx = getIdx(pList, (r,c))
        if idx != -1:
            tmp = pList[idx][1]
            if checkPosition(result, r,c,f):
                result = [(r,c), tmp, f]
                target = ((r,c), tmp)
        for i in range(4):
            nr, nc = [r+dr[i], c+dc[i]]
            if nr < 0 or nr >= N: continue
            if nc < 0 or nc >= N: continue
            if board[nr][nc] == 1: continue
            if visit[nr][nc]: continue
            q.append([nr,nc,f+1])
    if (target != -1): pList.remove(target)
    return result

def moveToDestination(start, end):
    q = deque()
    visit = [[False] * N for _ in range(N)]
    dr = [-1, 0, 0, 1]
    dc = [0, -1, 1, 0]
    q.append(([start[0], start[1], 0]))
    while q:
        r,c,f = q.popleft()
        if visit[r][c]: continue
        visit[r][c] = True
        if (r,c) == end:
            return f
        for i in range(4):
            nr, nc = [r+dr[i], c+dc[i]]
            if nr < 0 or nr >= N: continue
            if nc < 0 or nc >= N: continue
            if board[nr][nc] == 1: continue
            if visit[nr][nc]: continue
            q.append([nr,nc,f+1])
    return -1

def solution(board, pList, taxi, fuel):
    taxi = [taxi[0]-1, taxi[1]-1]
    while True:
        # 가장 가까운 승객 위치 찾기
        # 반환값: 승객 탑승 위치, 승객 하차 위치, 탑승 위치까지 연료 소모량
        result = findCloseGuest(board, taxi, pList)
        if result == -1: return -1
        start, end, useFuelToStart = result
        # 택시 위치 승객 탑승 위치로 변경
        taxi = [start[0], start[1]]
        # 목적지로 이동
        # 반환값: 사용한 연료 소모량 
        useFuelToEnd = moveToDestination(start, end)
        if useFuelToEnd == -1: return -1
        # 택시 위치 탑승 하차 위치로 변경
        taxi = [end[0], end[1]]
        # 남은 연료량 계산, 남은 연료가 0 미만일 경우 return -1
        fuel = fuel - useFuelToStart - useFuelToEnd
        if fuel < 0:
            return -1
        # 연료 채우기
        fuel += useFuelToEnd*2
        if len(pList) == 0:
            return fuel



print(solution(board, pList, taxi, fuel))

