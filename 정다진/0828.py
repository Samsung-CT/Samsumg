# baekjoon 12100

from copy import deepcopy
N = int(input())

graph = []
for i in range(N):
    graph.append(list(map(int, input().split())))

# 이동 함수
# 방향변수(0,1,2,3), board
def move(board, dir):
    # 상하좌우 같은 수 있나 케이스 나눠서 찾기
    # 1) 상 방향에 같은 수 있는 경우
    # 위 / 아래 이동
    if dir == 0:
        for i in range(N):
            top = N - 1
            for j in range(N - 2, -1, -1):
                if board[i][j]:
                    tmp = board[i][j]
                    board[i][j] = 0
                    if board[i][top] == 0:
                        board[i][top] = tmp
                    elif board[i][top] == tmp:
                        board[i][top] = tmp * 2
                        top -= 1
                    else:
                        top -= 1
                        board[i][top] = tmp

    # 2) 하 방향에 같은 수 있는 경우
    # 위 / 아래 이동
    elif dir == 1:
        for i in range(N):
            top = 0
            for j in range(1, N):
                if board[i][j]:
                    tmp = board[i][j]
                    board[i][j] = 0
                    if board[i][top] == 0:
                        board[i][top] = tmp
                    elif board[i][top] == tmp:
                        board[i][top] = tmp * 2
                        top += 1
                    else:
                        top += 1
                        board[i][top] = tmp

    # 3) 좌 방향에 같은 수 있는 경우
    # 오른쪽 / 왼쪽 이동
    elif dir == 2:
        for j in range(N):
            top = N - 1
            for i in range(N - 2, -1, -1):
                if board[i][j]:
                    tmp = board[i][j]
                    board[i][j] = 0
                    if board[top][j] == 0:
                        board[top][j] = tmp
                    elif board[top][j] == tmp:
                        board[top][j] = tmp * 2
                        top -= 1
                    else:
                        top -= 1
                        board[top][j] = tmp
    
    # 4) 우 방향에 같은 수 있는 경우
    # 오른쪽 / 왼쪽 이동
    else:
        for j in range(N):
            top = 0
            for i in range(1, N):
                if board[i][j]:
                    tmp = board[i][j]
                    board[i][j] = 0
                    if board[top][j] == 0:
                        board[top][j] = tmp
                    elif board[top][j] == tmp:
                        board[top][j] = tmp * 2
                        top += 1
                    else:
                        top += 1
                        board[top][j] = tmp

    return board


# 최대 5번만 움직일 수 있음
def dfs(board, count):
    global answer
    if count == 5:
        for i in range(N):
            for j in range(N):
                answer = max(answer, board[i][j])
        return
        
    for i in range(4):
        tmp_board = move(deepcopy(board), i)
        dfs(tmp_board, count + 1)

answer = 0
dfs(graph, 0)

# board에서 가장 큰 값 출력
print(answer)