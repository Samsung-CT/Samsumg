import sys
from collections import deque
from itertools import combinations
input=sys.stdin.readline

n=int(input())
board=[list(map(int,input().split())) for _ in range(n)]


#스코어 계산 함수
def score_count():
    q=deque()
    delta=[[-1,0],[1,0],[0,-1],[0,1]]
    visited=[[0 for _ in range(n)] for _ in range(n)]

    # init 그룹만들기 (visited 로 그룹화)
    group=[] #[그룹이름, 칸의 값, 칸의 수]  참고 : group[그룹이름-1][0]은 그룹이름과 같음
    group_num=0

    for start_row in range(n):
        for start_col in range(n):
            if visited[start_row][start_col]==0: #새로운 그룹이 발생
                group_num = group_num + 1
                q.append([start_row,start_col])
                visited[start_row][start_col]=group_num
                group.append([group_num, board[start_row][start_col], 1]) #[그룹이름, 칸의 값, 칸의 수]

            while q:
                [row,col]=q.popleft()
                for d in delta:
                    next_row=row+d[0]
                    next_col=col+d[1]
                    if 0<=next_row<n and 0<=next_col<n: # 벽 조건
                        if board[next_row][next_col]==board[row][col] and visited[next_row][next_col]==0: #상하좌우 탐색해서 다음꺼랑 같고, 방문하지 않았다면
                            q.append([next_row,next_col])
                            visited[next_row][next_col]=group_num
                            group[group_num-1][2]=group[group_num-1][2]+1

    #변의 개수 계산
    group_list=[i for i in range(1,group_num+1)]
    combi=list(combinations(group_list,2))
    group_match_cnt=[] # [group1, group2,맞닿은 변의 수]


    for case in combi:
        group1,group2=case
        cnt=0

        for row in range(n):
            for col in range(n):
                if visited[row][col]==group1: #group1일때

                    for d in delta: # 상하좌우 탐색해서,
                        if 0<=row+d[0]<n and 0<=col+d[1]<n: # 일단은 벽은 아닐때
                            if visited[row+d[0]][col+d[1]]==group2: #group2를 찾으면
                                cnt=cnt+1
        group_match_cnt.append([group1,group2,cnt])


    #그룹 간 조화로움 계산 : (group1칸수 + gorup2칸수) * (group1 값 * group2 값) * (group1과 group2가 맞닿은 변의 수 )
    harmony=0
    for [group1,group2,side] in group_match_cnt:
        res1=group[group1-1][1]*group[group2-1][1]
        res2=group[group1-1][2]+group[group2-1][2]

        harmony=harmony+res1*res2*side
    return harmony


#십자가 모양 회전 함수   [n//2,n//2]는 회전 안함
def big_rotate():
    for i in range(n//2):
        a=board[n//2][i]
        board[n//2][i]=board[i][n//2]
        board[i][n//2]=board[n//2][(n-1)-i]
        board[n//2][(n-1)-i]=board[(n-1)-i][n//2]
        board[(n-1)-i][n//2]=a


#오른쪽 90도 회전 함수 (정사각형 네구역 회전 시키기 위한 함수)
def rotate(size,board):
    new_board=[[0 for _ in range(size)] for _ in range(size)]
    for row in range(size):
        for col in range(size):
            new_board[row][col]=board[size-1-col][row]
    return new_board


#정사각형 회전 함수 (정사각형 네구역을 회전시키기 위한 함수)
def mini_rotate(row_start,row_end,col_start,col_end):
    square = []  # 초기화
    real_square = [[0 for _ in range(n // 2)] for _ in range(n // 2)]

    for row in range(row_start, row_end):
        for col in range(col_start, col_end):
            square.append(board[row][col])  # 각 영역 square에 담기

    for row in range(0, n // 2):
        for col in range(0, n // 2):
            real_square[row][col] = square.pop()  # 사각형 모양으로 만들기

    result_square = rotate(n // 2, real_square)  # 90도 회전

    for row in range(0, n // 2):
        for col in range(0, n // 2):
            square.append(result_square[row][col])  # 사각형 모양 풀기

    for row in range(row_start, row_end):
        for col in range(col_start, col_end):
            board[row][col] = square.pop()  # 값 다시 넣기
half=n//2
def rotate_4():
    mini_rotate(0, half, 0, half)
    mini_rotate(half+1, n, 0, half)
    mini_rotate(0, half, half+1, n)
    mini_rotate(half+1, n, half+1, n)






#init 실행
sum=score_count()

#main 실행
for _ in range(3):
    big_rotate()
    rotate_4()
    sum=sum+score_count()

#result 실행
print(sum)