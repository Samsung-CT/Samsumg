import sys
from collections import deque

input=sys.stdin.readline

#제출시 아래 주석 해제!!!!!!!!!!!!!
#n,m,k=map(int,input().split())
#board=[list(map(int,input().split())) for _ in range(n)]
#wall=[list(map(int,input().split())) for _ in range(m)]


n,m,k=5,2,2
board=[[0, 0, 0, 0, 0],
       [4, 0, 1, 1, 1],
       [0, 0, 1, 1, 0],
       [0, 0, 0, 0, 0],
       [0, 3, 0, 0, 0]]
walls=[[3,2,0],[3,2,1]] #walls는 1부터 시작인거 확인! #0 바로 위 #1바로 왼쪽


#init
offices=[]
airconditions=[]
for row in range(n): #사무실 위치와 에어컨의 위치를 찾는 과정
    for col in range(n):
        if board[row][col]==1: 
            offices.append([row,col])
            board[row][col]=0
        elif 2<=board[row][col]<=5: #2,3,4,5 == 좌,상,우,하
            airconditions.append([row,col,board[row][col]])
            board[row][col]=0


collasped_time=0 #경과 시간



#main
while(True):
    if collasped_time>100: # 경과 시간이 100분 이상일 시
        collasped_time=-1 # -1
        break
    else: # 결과 시간이 100분이 아닌 경우에 대한 main
        
        #에어컨 확산
        for aircondition in airconditions: # 각 에어컨들에 대해서
            [row,col,direction]=aircondition
            if direction==2:
                d=[0,-1]
                diagonal_r=[1,-1]
                diagonal_l=[-1,-1]
                
            elif direction==3:
                d=[-1,0]
                diagonal_r=[-1,-1]
                diaconal_l=[-1,1]
                
            elif direction==4:
                d=[0,1]
                diagonal_r=[-1,1]
                diagonal_l=[1,1]
                
            else: # 5일때
                d=[1,0]
                diagonal_r=[1,1]
                diagonal_l=[1,-1]
                
            
            q=deque()
            for i in range(5): #0,1,2,3,4 # 한단계씩 확산
                if i==0: # 첫번째 경우만 계산 (예외사항 없음)
                    board[row+d[0]][col+d[1]]=5
                    q.append([row+d[0],col+d[1],5])
                else: #첫번째 경우가 아닌 경우
                    while 1:
                        [row,col,power]=q.popleft()
                        column=[]
                        row_nextr,col_nextr=row+diagonal_r[0],col+diagonal_r[1]
                        row_nextl,col_nextl=row+diagonal_l[0],col+diagonal_l[1]
                        row_next,col_next=row+d[0]+col+d[1]
                        if 0<=row_next<n and 0<=col_next<n: #직진 벽조건
                            if row




                    
                    

                
                
                
                

