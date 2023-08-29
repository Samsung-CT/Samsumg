N = int(input())
board = []
for _ in range(N):
    temp = list(map(int, input().split()))
    board.append(temp)

import copy


def move(board, D):
    temp_board = []
    if D == 'L':
        for row in range(N):
            check = [False] * N
            line = board[row]
            temp_line = []
            for i in range(N):
                if line[i] == 0:
                    continue
                if check[i] == True:
                    continue
                if i == N-1 and check[i] == False:
                    temp_line.append(line[i])
                    check[i] = True
                    break
                    
                for j in range(i+1, N):
                    if line[j] != 0 and line[i] == line[j]:
                        temp_line.append(line[i]*2)
                        check[i] = True
                        check[j] = True
                        break
                    elif line[j] != 0 and line[i] != line[j]:
                        temp_line.append(line[i])
                        check[i] = True
                        break
                    if j == N-1:
                        temp_line.append(line[i])
                        check[i] = True
                        
            temp_line = temp_line + [0] * (N-len(temp_line))
            temp_board.append(temp_line)
            
    if D == "R":
        for row in range(N):
            check = [False] * N
            line = board[row]
            line.reverse()
            temp_line = []
            for i in range(N):
                if line[i] == 0:
                    continue
                if check[i] == True:
                    continue
                if i == N-1 and check[i] == False:
                    temp_line.append(line[i])
                    check[i] = True
                    break
                    
                for j in range(i+1, N):
                    if line[j] != 0 and line[i] == line[j]:
                        temp_line.append(line[i]*2)
                        check[i] = True
                        check[j] = True
                        break
                    elif line[j] != 0 and line[i] != line[j]:
                        temp_line.append(line[i])
                        check[i] = True
                        break
                    if j == N-1:
                        temp_line.append(line[i])
                        check[i] = True
                        
            temp_line = temp_line + [0] * (N-len(temp_line))
            temp_line.reverse()
            temp_board.append(temp_line)
            
    if D == "U":
        board = rotate_CCW(board)
        board = move(board, D="L")
        board = rotate_CW(board)
        return board
    if D == "D":
        board = rotate_CW(board)
        board = move(board, D="L")
        board = rotate_CCW(board)
        return board
    
    
    return temp_board


def rotate_CW(board):
    N = len(board)
    temp_board = [[0 for _ in range(N)] for __ in range(N)]
    for row in range(N):
        for col in range(N):
            temp_board[col][N-row-1] = board[row][col]
    return temp_board
    
    
def rotate_CCW(board):
    N = len(board)
    temp_board = [[0 for _ in range(N)] for __ in range(N)]
    for row in range(N):
        for col in range(N):
            temp_board[N-1-col][row] = board[row][col]
    return temp_board
    
def find_max(board):
    max_value = max(map(max, board))
    return max_value




max_values = []

def dfs(board, D, step):
    board = move(board, D)
    if step == 5:
        max_value = find_max(board)
        max_values.append(max_value)
        return board
    
    for d in ["R", "L", "U", "D"]:
        dfs(copy.deepcopy(board), d, step+1)
    return board

dfs(board, "R", 1)
dfs(board, "L", 1)
dfs(board, "U", 1)
dfs(board, "D", 1)

print(max(max_values))
