n = int(input())
picture = []
for i in range(n):
    temp = list(map(int, input().split()))
    picture.append(temp)



import copy

def search_adj(picture, i, j):
    cands = [[i+1, j], [i-1, j], [i, j+1], [i, j-1]]
    results = []
    for temp in cands:
        if n > temp[0] >=0 and n > temp[1] >= 0:
            results.append(temp)
    return results
                
    
def dfs_group(picture, num, i, j, group, visited):
    visited.append([i,j])
    adjs = search_adj(picture, i, j)
    for adj in adjs:
        a, b = adj
        if adj not in visited and picture[a][b] == num:
            group.append(adj)
            dfs_group(picture, num, a, b, group, visited)
    return group


def grouping(picture):
    g2p = {} # group2pos
    p2g = {} # pos2group
    visited = []
    for i in range(n):
        for j in range(n):
            if [i,j] in visited:
                continue
            group = [[i,j]]
            num = picture[i][j]
            group = dfs_group(picture, num, i, j, group, visited)
            group_num = len(g2p)
            g2p[group_num] = {'num':num, 'group':group}
            for pos in group:
                p2g[(pos[0], pos[1])] = group_num
            visited.extend(group)
            
    return  g2p, p2g


def count_meet(picture, g2p, p2g):
    # 전체 그룹 간에 겹치는 면 개수 세기
    g2g_meet = {}
    group_num = len(g2p)
    for group1 in range(group_num):
        for group2 in range(group1+1, group_num):
            c = count_meet_(picture, group1, group2, g2p, p2g)
            g2g_meet[(group1, group2)] = c
            g2g_meet[(group2, group1)] = c
    return  g2g_meet


def count_meet_(picture, g1, g2, g2p, p2g):
    count = 0
    positions = g2p[g1]['group']
    for pos in positions:
        adjs = search_adj(picture, pos[0], pos[1])
        for adj in adjs:
            if p2g[(adj[0], adj[1])] == g2:
                count += 1
    return count
    # 두 그룹 간에 겹치는 면 개수 세기
    
    
def rotation(picture):
    n = len(picture)
    mid = n//2
    # 1. cross
    # 십자 부분만 반시계로 90도 회전
    temp_picture = [[0 for _ in range(n)] for __ in range(n)]
    for i in range(n):
        temp_picture[mid][i] = picture[i][mid]
    for i in range(n):
        temp_picture[n-i-1][mid] = picture[mid][i]
    for i in range(n):
        picture[mid][i] = temp_picture[mid][i]
    for i in range(n):
        picture[i][mid] = temp_picture[i][mid]
    
    # 2. cross^
    box_temp1 = [[0 for _ in range(mid)] for __ in range(mid)]
    box_temp2 = [[0 for _ in range(mid)] for __ in range(mid)]
    box_temp3 = [[0 for _ in range(mid)] for __ in range(mid)]
    box_temp4 = [[0 for _ in range(mid)] for __ in range(mid)]
    for i in range(mid):
        for j in range(mid):
            box_temp1[i][j] = picture[i][j]
    for i in range(mid):
        for j in range(mid):
            box_temp2[i][j] = picture[i + mid + 1][j]
    for i in range(mid):
        for j in range(mid):
            box_temp3[i][j] = picture[i][j + mid + 1]
    for i in range(mid):
        for j in range(mid):
            box_temp4[i][j] = picture[i + mid + 1][j + mid + 1]
    # 각 박스 회전
    box_temp1 = rotate_box(box_temp1)
    box_temp2 = rotate_box(box_temp2)
    box_temp3 = rotate_box(box_temp3)
    box_temp4 = rotate_box(box_temp4)
    
    # 각 박스 회전한 값 할당
    for i in range(mid):
        for j in range(mid):
            picture[i][j] = box_temp1[i][j]
    for i in range(mid):
        for j in range(mid):
            picture[i + mid + 1][j] = box_temp2[i][j]
    for i in range(mid):
        for j in range(mid):
            picture[i][j + mid + 1] = box_temp3[i][j]
    for i in range(mid):
        for j in range(mid):
            picture[i + mid + 1][j + mid + 1] = box_temp4[i][j]
    
    return picture
    

# def rotate_box(box):
#     # 박스를 시계방향으로 90도 회전
#     import numpy as np
#     box = np.array(box)
#     box = np.rot90(box, k=1, axes=(1,0))
#     return box.tolist()

def rotate_box(box):
    '''박스를 시계방향으로 90도 회전
    * 사등분으로 나눠진 박스 중 하나의 박스를 돌리기'''
    length = len(box)
    temp_box = [[0 for _ in range(length)] for __ in range(length)]
    for i in range(length):
        for j in range(length):
            temp_box[j][length-i-1] = box[i][j]
    return temp_box

def get_score(picture, g2p, p2g, g2g_meet):
    score = 0
    group_num = len(g2p)
    for g1 in range(group_num):
        for g2 in range(g1+1, group_num):
            score += get_score_(g2p, p2g, g1, g2, g2g_meet)
                
    return  score


def get_score_(g2p, p2g, g1, g2, g2g_meet):
    # (the number of squares in group a + the number of squares in group b) 
    # x the value of the number representing group a 
    # x the value of the number representing group b 
    # x the number of sides that group a and group b touch.
    a1 = len(g2p[g1]['group']) + len(g2p[g2]['group'])
    a2 = g2p[g1]['num']
    a3 = g2p[g2]['num']
    a4 = g2g_meet[(g1,g2)]
    return a1 * a2 * a3 * a4
    
    
    
# 1. 그룹 분리 - grouping
# 2. 그룹간에 접하는 면 개수
# 3. 점수 계산
# 4. 로테이션 후 점수 계산
# 5. 합

def sol(picture):
    # 1. 
    g2p, p2g = grouping(picture)

    # 2.
    g2g_meet = count_meet(picture, g2p, p2g)
    
    # 3. 
    score = get_score(picture, g2p, p2g, g2g_meet)
    return score

score = sol(picture)
# 4.
rot1 = rotation(copy.deepcopy(picture))
rot2 = rotation(copy.deepcopy(rot1))
rot3 = rotation(copy.deepcopy(rot2))
score1 = sol(rot1)
score2 = sol(rot2)
score3 = sol(rot3)

# 5. 
print(score + score1 + score2 + score3)
