import sys
from collections import deque

input = sys.stdin.readline

N, M = map(int, input().split(" "))
board = []
for _ in range(N):
    board.append(list(map(int, input().split(" "))))

dr = [0,0,1,-1]
dc = [1,-1,0,0]

def findLargeBlock(board, start, visit):
    q = deque()
    q.append(start)
    size = 0
    rbSize = 0
    blockType = board[start[0]][start[1]]
    while q:
        r, c = q.popleft()
        if visit[r][c]:
            continue
        size+=1
        visit[r][c] = True
        if board[r][c] == 0:
            rbSize+=1
        for i in range(4):
            nr, nc = r+dr[i], c+dc[i]
            if nr < 0 or nr >= N:
                continue
            if nc < 0 or nc >= N:
                continue
            if board[nr][nc] != blockType and board[nr][nc] != 0:
                continue
            if visit[nr][nc]:
                continue
            q.append([nr,nc])
    for r in range(N):
        for c in range(N):
            if board[r][c] == 0:
                visit[r][c] = False
    return [size, rbSize, start]

def checkBlock(blockSize, rbBlockSize, pivotBlock, size, rbSize, pivot):
    if blockSize < size:
        return True
    if blockSize == size and rbBlockSize < rbSize:
        return True
    if blockSize == size and rbBlockSize == rbSize and pivotBlock[0] < pivot[0]:
        return True
    if blockSize == size and rbBlockSize == rbSize and pivotBlock[0] == pivot[0] and pivotBlock[1] < pivot[1]:
        return True
    return False

def deleteBlock(board, pivotBlock):
    q = deque()
    q.append(pivotBlock)
    blockType = board[pivotBlock[0]][pivotBlock[1]]
    while q:
        r, c = q.popleft()
        if board[r][c] == -2:
            continue
        board[r][c] = -2
        for i in range(4):
            nr, nc = r+dr[i], c+dc[i]
            if nr < 0 or nr >= N:
                continue
            if nc < 0 or nc >= N:
                continue
            if board[nr][nc] != blockType and board[nr][nc] != 0:
                continue
            if board[nr][nc] == -2:
                continue
            q.append([nr,nc])

def gravity(board):
    for c in range(N):
        start = N-1
        r = N-1
        while start > 0:
            while board[r][c] == -2:
                if r == 0:
                    break
                r-=1
            if start != r and board[r][c] != -1:
                board[start][c] = board[r][c]
                board[r][c] = -2
            start-=1
            r = start

def rotate(board):
    newBoard = [[0]*N for _ in range(N)]
    for r in range(N):
        for c in range(N):
            newBoard[r][c] = board[c][N-r-1]
    return newBoard

score = 0
# 블록이 존재하는 동안 반복
while True:
    blockSize=0
    rbBlockSize=0
    pivotBlock = [0,0]
    # 블록 그룹 찾기
    visit = [[False]*N for _ in range(N)]
    for r in range(N):
        for c in range(N):
            if board[r][c] > 0:
                size, rbSize, pivot = findLargeBlock(board, [r,c], visit)
                if checkBlock(blockSize, rbBlockSize, pivotBlock, size, rbSize, pivot):
                    blockSize = size
                    rbBlockSize = rbSize
                    pivotBlock = pivot
    # 블록 존재하는지 체크
    if blockSize < 2:
        break
    # 찾은 블록 그룹 제거
    score += blockSize**2
    deleteBlock(board, pivotBlock)
    # 중력 작용
    gravity(board)
    # 회전
    board = rotate(board)
    # 중력작용
    gravity(board)

print(score)