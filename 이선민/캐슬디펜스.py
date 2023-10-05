import sys
from collections import deque

input = sys.stdin.readline

n, m, d = map(int, input().split(" "))

board = []
initBoard = []
for _ in range(n):
    tmp = list(map(int, input().split(" ")))
    board.append(tmp)
    initBoard.append(tmp)

def combi(arr, count):
    if count == 1:
        return [[x] for x in arr]
    result = []
    for index in range(len(arr)):
        subCombi = combi(arr[index+1:], count-1)
        tmp = [[arr[index]] + sub for sub in subCombi]
        result += tmp
    return result

def checkBoard(board):
    for r in range(n):
        for c in range(m):
            if board[r][c] == 1:
                return True
    return False

def attack(board, shoot, dis):
    q = deque()
    q.append([n-1, shoot, 1])
    visit = [[False] * m for _ in range(n)]
    dr = [0, -1, 0]
    dc = [-1, 0, 1]
    while q:
        r, c, d = q.popleft()
        if d > dis:
            continue
        if visit[r][c]:
            continue
        if board[r][c] == 1:
            return [r,c]
        visit[r][c] = True
        for i in range(3):
            nr = r + dr[i]
            nc = c + dc[i]
            if nr < 0 or nr >= n:
                continue
            if nc < 0 or nc >= m:
                continue
            q.append([nr, nc, d+1])
    return None
        

shooters = list(combi([i for i in range(m)], 3))
result = []

for shooter in shooters:
    total = 0
    board = [[x for x in row] for row in initBoard]
    while checkBoard(board):
        # 궁수 공격
        targetList = []
        for shoot in shooter:
            shootTarget = attack(board, shoot, d)
            if shootTarget:
                targetList.append(shootTarget)
        shootCount = 0
        for target in targetList:
            if board[target[0]][target[1]] == 1:
                shootCount += 1
                board[target[0]][target[1]] = 0
        total += shootCount
        # 적 아래로 한칸 이동
        board = [[0 for _ in range(m)]] + board
        board.pop()
    result.append(total)
print(max(result))