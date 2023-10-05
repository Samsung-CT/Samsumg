N,M,K = map(int,input().split())
maze = []
for _ in range(N):
    maze.append(list(map(int,input().split())))
people = []
for _ in range(M):
    person = list(map(int,input().split()))
    people.append([person[0]-1, person[1]-1])
exit = list(map(int,input().split()))
exit = [exit[0]-1, exit[1]-1]
temp_maze = [m[:] for m in maze]

def move():
    moving_points = 0
    new_people = []
    for idx, person in enumerate(people):
        cur_distance = abs(person[0]-exit[0]) + abs(person[1]-exit[1])
        cands = [[person[0]-1, person[1]], [person[0]+1, person[1]], [person[0], person[1]-1], [person[0], person[1]+1]]
        isdone = False
        for cand in cands:
            if N > cand[0] >= 0 and N > cand[1] >= 0:
                if maze[cand[0]][cand[1]] > 0:
                    continue
                    
                distance = abs(cand[0]-exit[0]) + abs(cand[1]-exit[1])
                if distance == 0:
                    moving_points += 1
                    isdone = True
                    break
                if distance < cur_distance:
                    moving_points += 1
                    new_people.append(cand[:])
                    isdone = True
                    break
        if isdone == False:
            new_people.append(person[:])
                    
    return new_people, moving_points


def find_square():
    # 최소 변 길이 찾기
    min_length = 9999
    for person in people:
        length = max(abs(person[0]-exit[0]), abs(person[1]-exit[1]))
        min_length = min(min_length, length)
        
    # 좌상단 꼭지점 탐색
    for row in range(0, N-min_length):
        for col in range(0, N-min_length):
            person_check = False
            exit_check = False
            if row <= exit[0] <= row+min_length and col <= exit[1] <= col+min_length:
                exit_check = True
            else:
                continue
                
            for person in people:
                if row <= person[0] <= row+min_length and col <= person[1] <= col+min_length:
                    person_check = True
                    break
            if person_check == True and exit_check == True:
                return [row, col], min_length
            
    # 좌상단 꼭지점 탐색
#     min_row = max(0, exit[0]-min_length)
#     max_row = min(N-1-min_length, exit[0])
#     min_col = max(0, exit[1]-min_length)
#     max_col = min(N-1-min_length, exit[1])
#     for row in range(min_row, max_row+1):
#         for col in range(min_col, max_col+1):
#             point = [row, col]
#             for person in people:
#                 if row <= person[0] <= row+min_length and col <= person[1] <= col+min_length:
#                     return [row,col], min_length

            
def rotation(vertex, length):
    # 미로 회전
    x0 = vertex[0]
    y0 = vertex[1]
    for row in range(length+1):
        for col in range(length+1):
            temp_maze[col][length-row] = maze[x0+row][y0+col]
            
    for row in range(length+1):
        for col in range(length+1):
            if temp_maze[row][col] > 0:
                maze[x0+row][y0+col] = temp_maze[row][col] - 1
            else:
                maze[x0+row][y0+col] = temp_maze[row][col]
            
    
    # 사람 회전
    new_people = []
    for person in people:
        if x0 <= person[0] <= x0+length and y0 <= person[1] <= y0+length:
            x = person[0]
            y = person[1]
            x_0 = x - x0
            y_0 = y - y0
            new_person = [x0 + y_0, y0 + length-x_0]
            new_people.append(new_person[:])
        else:
            new_people.append(person[:])
    
    # 출구 회전
    x = exit[0]
    y = exit[1]
    x_0 = x - x0
    y_0 = y - y0
    new_exit = [x0 + y_0, y0 + length-x_0]
    
    return new_people, new_exit


answer = 0
for _ in range(K):
    people, moving_points = move()
    answer += moving_points
    if len(people) == 0:
        break
    vertex, length = find_square()
    people, exit = rotation(vertex, length)
print(answer)
print(exit[0]+1,exit[1]+1)
