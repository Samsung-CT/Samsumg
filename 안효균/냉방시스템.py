import copy

n, m, k = map(int, input().split())
board = []
walls = []
for _ in range(n):
    temp = list(map(int, input().split()))
    board.append(temp)
for _ in range(m):
    temp = list(map(int, input().split()))
    walls.append([temp[0]-1, temp[1]-1, temp[2]])
    
cool_board = [[0 for _ in range(n)] for __ in range(n)]



def blow_air(starts, value, direction):
    for start in starts:
        cool_board[start[0]][start[1]] += value
    if value == 1:
        return
    # s가 0 : 위에 벽
    # s가 1 : 왼쪽에 벽
    
    next_starts = []
    for start in starts:
        if direction == 2: # 왼쪽
            if [start[0], start[1], 1] not in walls:
                next_starts.append([start[0], start[1]-1])
            if [start[0], start[1], 0] not in walls and [start[0]-1, start[1], 1] not in walls:
                next_starts.append([start[0]-1, start[1]-1])
            if [start[0]+1, start[1], 0] not in walls and [start[0]+1, start[1], 1] not in walls:
                next_starts.append([start[0]+1, start[1]-1])
                
        elif direction == 3: # 위
            if [start[0], start[1], 0] not in walls:
                next_starts.append([start[0]-1, start[1]])
            if [start[0], start[1], 1] not in walls and [start[0], start[1]-1, 0] not in walls:
                next_starts.append([start[0]-1, start[1]-1])
            if [start[0], start[1]+1, 1] not in walls and [start[0], start[1]+1, 0] not in walls:
                next_starts.append([start[0]-1, start[1]+1])
            
        elif direction == 4: # 오른쪽
            if [start[0], start[1]+1, 1] not in walls:
                next_starts.append([start[0], start[1]+1])
            if [start[0], start[1], 0] not in walls and [start[0]-1, start[1]+1, 1] not in walls:
                next_starts.append([start[0]-1, start[1]+1])
            if [start[0]+1, start[1], 0] not in walls and [start[0]+1, start[1]+1, 1] not in walls:
                next_starts.append([start[0]+1, start[1]+1])
            
        elif direction == 5: # 아래
            if [start[0]+1, start[1], 0] not in walls:
                next_starts.append([start[0]+1, start[1]])
            if [start[0], start[1], 1] not in walls and [start[0]+1, start[1]-1, 0] not in walls:
                next_starts.append([start[0]+1, start[1]-1])
            if [start[0], start[1]+1, 1] not in walls and [start[0]+1, start[1]+1, 0] not in walls:
                next_starts.append([start[0]+1, start[1]+1])
    temp = []
    for next_start in next_starts:
        if n > next_start[0] >= 0 and n > next_start[1] >= 0 and next_start not in temp:
            temp.append(next_start)
    next_starts = temp
    
    blow_air(next_starts, value-1, direction)
    

def mix_air(pos):
    links = []
    # s가 0 : 위에 벽
    # s가 1 : 왼쪽에 벽
    # 위
    if [pos[0], pos[1], 0] not in walls:
        links.append([pos[0]-1, pos[1]])
    # 오른
    if [pos[0], pos[1]+1, 1] not in walls:
        links.append([pos[0], pos[1]+1])
    # 왼
    if [pos[0], pos[1], 1] not in walls:
        links.append([pos[0], pos[1]-1])
    # 아래
    if [pos[0]+1, pos[1], 0] not in walls:
        links.append([pos[0]+1, pos[1]])
    
    temp = []
    for next_start in links:
        if n > next_start[0] >= 0 and n > next_start[1] >= 0:
            temp.append(next_start)
    links = temp
    
    for link in links:
        orig = cool_board[pos[0]][pos[1]]
        tag = cool_board[link[0]][link[1]]
        diff = abs(orig - tag) // 4
        
        if diff >= 1:
            if orig > tag:
                temp_cool[pos[0]][pos[1]] -= diff
            else:
                temp_cool[pos[0]][pos[1]] += diff
            
        
    
def down1deg(pos):
    if cool_board[pos[0]][pos[1]] >= 1:
        cool_board[pos[0]][pos[1]] -= 1
    
            

        
minute = 0

while True:
    minute += 1

    for row in range(n):
        for col in range(n):
            if board[row][col] == 2: # 왼쪽
                blow_air([[row, col-1]], 5, board[row][col])
            elif board[row][col] == 3: # 위
                blow_air([[row-1, col]], 5, board[row][col])
            elif board[row][col] == 4: # 오른쪽
                blow_air([[row, col+1]], 5, board[row][col])
            elif board[row][col] == 5: # 아래
                blow_air([[row+1, col]], 5, board[row][col])
    temp_cool = copy.deepcopy(cool_board)

    for i in range(n):
        for j in range(n):
            mix_air([i,j])
    cool_board = temp_cool
    
    #3. 외벽에 있는 칸에 대해서만 시원함이 1씩 감소합니다.
    for row in range(n):
        for col in range(n):
            if row == 0 or row == n-1:
                down1deg([row, col])
            else:
                if col == 0 or col == n-1:
                    down1deg([row, col])
    

    # 4. 사무실 온도 검사
    check = True
    for row in range(n):
        for col in range(n):
            if board[row][col] == 1:
                if cool_board[row][col] < k:
                    check = False
    if check == True:
        break
    if minute > 100:
        minute = -1
        break
print(minute)
