import sys
from collections import deque

input = sys.stdin.readline

N = int(input())
board = []
for _ in range(N):
    board.append(list(map(int, input().split(" "))))

def sumArr(start, end, di, notZeros):
    prev = 0
    tmp = []
    for i in range(start, end, di):
        if prev == 0:
            tmp.append(notZeros[i])
            prev = notZeros[i]
        elif prev == notZeros[i]:
            tmp.pop()
            tmp.append(notZeros[i] + prev)
            prev = 0
        else:
            tmp.append(notZeros[i])
            prev = notZeros[i]
    for _ in range(len(tmp), N):
        tmp.append(0)
    return tmp

def moveRight(current):
    newBoard = []
    for row in current:
        notZeros = []
        for num in row:
            if num != 0:
                notZeros.append(num)
        tmp = sumArr(len(notZeros)-1, -1, -1, notZeros)
        tmp.reverse()
        newBoard.append(tmp)
    return newBoard

def moveLeft(current):
    newBoard = []
    for row in current:
        notZeros = []
        for num in row: 
            if num != 0:
                notZeros.append(num)
        tmp = sumArr(0, len(notZeros), 1, notZeros)
        newBoard.append(tmp)
    return newBoard

def moveDown(current):
    newBoard = [[0] * N for _ in range(N)]
    for c in range(N):
        notZeros = []
        for r in range(N):
            if current[r][c] != 0:
                notZeros.append(current[r][c])
        tmp = sumArr(len(notZeros)-1, -1, -1, notZeros)
        tmp.reverse()
        for r in range(N):
            newBoard[r][c] = tmp[r]
    return newBoard

def moveUp(current):
    newBoard = [[0] * N for _ in range(N)]
    for c in range(N):
        notZeros = []
        for r in range(N):
            if current[r][c] != 0:
                notZeros.append(current[r][c])
        tmp = sumArr(0, len(notZeros), 1, notZeros)
        for r in range(N):
            newBoard[r][c] = tmp[r]
    return newBoard

        
def findMax(current):
    result = 0
    for r in range(N):
        for c in range(N):
            if result < current[r][c]:
                result = current[r][c]
    return result
            

q = deque()
q.append((board, 0))

ans = 0
while q:
    current, count = q.popleft()
    if count >= 5:
        tmp = findMax(current)
        if tmp > ans:
            ans = tmp
        continue
    q.append((moveRight(current), count+1))
    q.append((moveLeft(current), count+1))
    q.append((moveDown(current), count+1))
    q.append((moveUp(current), count+1))

print(ans)