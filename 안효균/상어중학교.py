N, M = map(int, input().split())
board = []
for i in range(N):
    temp = list(map(int, input().split()))
    board.append(temp)


import copy

'''
** 기준 블록 : 왼쪽 위 블록
** 여러 블록 그룹이 블록을 공유할 수 있음
'''

def find_adj(i, j):
    cands = []
    temp = [[i+1, j], [i-1,j], [i,j+1], [i,j-1]]
    for cand in temp:
        if N > cand[0] >= 0 and N > cand[1] >= 0:
            cands.append(cand)
    return cands


def dfs_step(pos, color, visited=[], check=[]):
    visited.append(pos)
    
    adjs = find_adj(pos[0], pos[1])
    for adj in adjs:
        if adj not in visited:
            c = board[adj[0]][adj[1]]
            if c == color or c == 0:
                visited = dfs_step(adj, color, visited)
    return visited
     
    
def find_groups():
    groups = []
    visited = []
    rainbows = []
    for i in range(N):
        for j in range(N):
            if board[i][j] == 0:
                rainbows.append([i,j])
                
    for i in range(N):
        for j in range(N):
            if [i,j] in visited:
                continue
            color = board[i][j]
            if color == -1 or color == None or color == 0:
                continue
            group = dfs_step([i,j], color, [], visited)
            if len(group) < 2:
                continue
            
            # 기준 블록 찾기
            cri = [100, 100]
            rainbow = 0
            for p in group: 
                if board[p[0]][p[1]] == 0: # 무지개 제외
                    rainbow += 1
                    continue
                if cri[0] > p[0]:
                    cri = copy.deepcopy(p)
                elif cri[0] == p[0] and cri[1] > p[1]:
                    cri = copy.deepcopy(p)
            
            # 이미 찾은 그룹 제외
            check = False
            for g in groups:
                len_, color_, cri_ = g['len'], g['color'], g['cri']
                if len(group) == len_ and color == color_ and cri == cri_:
                    check = True
                    break
            if check == False:
                groups.append({'group':group, 'len':len(group), 'color':color, 'cri':cri, 'rainbow':rainbow})
                for g in group:
                    if g not in rainbows:
                        visited.append(g)
                
    return groups


def find_main_group(groups):
    cands = []
    
    # 1. 크기가 가장 큰 그룹
    Max = 0
    for group in groups:
        Max = max(Max, group['len'])
    for group in groups:
        if group['len'] == Max:
            cands.append(group)
            
    if len(cands) == 1:
        return cands[0]
    
    
    # 2. 무지개 블록 수가 많은 것
    Max = 0
    cands_temp = []
    for group in cands:
        Max = max(Max, group['rainbow'])
    for group in cands:
        if group['rainbow'] == Max:
            cands_temp.append(group)
    
    if len(cands_temp) == 1:
        return cands_temp[0]
    
    
    # 3. 기준 블록 행이 큰 것
    cands = copy.deepcopy(cands_temp)
    Max = 0
    cands_temp = []
    for group in cands:
        Max = max(Max, group['cri'][0])
    for group in cands:
        if group['cri'][0] == Max:
            cands_temp.append(group)
    
    if len(cands_temp) == 1:
        return cands_temp[0]
    
    # 4. 기준 블록 열이 큰 것
    cands = copy.deepcopy(cands_temp)
    Max = 0
    cands_temp = []
    for group in cands:
        Max = max(Max, group['cri'][1])
    for group in cands:
        if group['cri'][1] == Max:
            cands_temp.append(group)
    
    if len(cands_temp) == 1:
        return cands_temp[0]
    else:
        print("Error 기준 블록 열 개수")

        
def delete_group(group):
    for pos in group['group']:
        board[pos[0]][pos[1]] = None
    
    
def gravity():    
    # temp_board = [[None for _ in range(N)] for __ in range(N)]
    for col in range(N):
        for row in range(N-1, -1, -1): #아래 행, 왼쪽 열부터 최대한 아래로 내리기
            color = board[row][col]
            if color == None or color == -1: # 비어있거나 검은색돌이면 pass
                # temp_board[row][col] = color
                continue
            else:
                cur_row = row
                for next_row in range(row+1, N):
                    if board[next_row][col] == -1:
                        break
                    if board[next_row][col] == None:
                        board[next_row][col] = board[cur_row][col]
                        board[cur_row][col] = None
                        cur_row = next_row
                    
                    
    return 


def rot_ccw():
    temp_board = [[None for _ in range(N)] for __ in range(N)]
    for row in range(N):
        for col in range(N-1, -1, -1):
            temp_board[N-1-col][row] = board[row][col]
    return temp_board
    
score = 0

while True:
    # 전체 그룹 찾기
    groups = find_groups()
    if len(groups) == 0:
        break

    # 큰 그룹 찾기
    group = find_main_group(groups)
    # 그룹 블록 제거하고 점수 획득
    score += group['len']**2
    delete_group(group)

    # 중력
    gravity()

    # 반시계 90도 회전
    board = rot_ccw()

    # 중력
    gravity()
    
print(score)
