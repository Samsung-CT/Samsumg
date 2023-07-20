import sys
from collections import deque

input = sys.stdin.readline

N, M = map(int, input().split(" "))
board = []
for _ in range(N):
    board.append(list(input())[:-1])

def getPosition(board, N, M):
    R, O, B = [], [], []
    for r in range(N):
        for c in range(M):
            if board[r][c] == "R":
                R = [r,c]
            elif board[r][c] == "B":
                B = [r,c]
            elif board[r][c] == "O":
                O = [r,c]
    return R,O,B

def move(r, c, i, board):
    dr = [0,0,1,-1]
    dc = [1,-1,0,0]
    distance = 1
    while True:
        newR = r + distance*dr[i]
        newC = c + distance*dc[i]
        if board[newR][newC] == "#":
            return [newR-dr[i], newC-dc[i], distance-1]
        if board[newR][newC] == "O":
            return [newR, newC, distance]
        distance+=1
    

def solution(board, N, M):
    R,O,B = getPosition(board, N, M)
    redq = deque()
    blueq = deque()
    redq.append(R)
    blueq.append(B)
    # 횟수 저장 및 방문 체크용
    visit = [[[[0] * M for _ in range(N)] for _ in range(M)] for _ in range(N)]
    visit[R[0]][R[1]][B[0]][B[1]] = 1
    dr = [0,0,1,-1]
    dc = [1,-1,0,0]
    while redq:
        rr, rc = redq.popleft()
        br, bc = blueq.popleft()
        if visit[rr][rc][br][bc] > 10:
            return -1
        for i in range(4):
            # 이동 방향으로 움직이기
            next_rr, next_rc, r_distance = move(rr, rc, i, board)
            next_br, next_bc, b_distance = move(br, bc, i, board)
            # 파란공이 구멍에 빠질 경우
            if (board[next_br][next_bc] == "O"):
                continue
            # 빨간공이 구멍에 빠질 경우 성공
            if (board[next_rr][next_rc] == "O"):
                return visit[rr][rc][br][bc]
            # 빨간공과 파란공 위치가 같을 경우
            if (next_rr == next_br and next_rc == next_bc):
                if r_distance > b_distance:
                    next_rr -= dr[i]
                    next_rc -= dc[i]
                else:
                    next_br -= dr[i]
                    next_bc -= dc[i]
            # 이미 방문한 경우
            if visit[next_rr][next_rc][next_br][next_bc]:
                continue
            redq.append([next_rr, next_rc])
            blueq.append([next_br, next_bc])
            visit[next_rr][next_rc][next_br][next_bc] = visit[rr][rc][br][bc] + 1
    return -1



print(solution(board, N, M))