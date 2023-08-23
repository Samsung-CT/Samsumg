import sys

input=sys.stdin.readline
N,L=map(int,input().split())
board=[list(map(int,input().split())) for _ in range(N)]


col_able=0
for row in range(N): 
    previous_height=board[row][0]
    col=1
    ramp_check=[0]*N
    while True:
        if board[row][col]!=previous_height:                # 높이가 다른 경우
            if previous_height-board[row][col]==1:          # 내려가는 경사로인 경우
                wrong=0                                     #L 길이만큼 탐색했을때 다른 높이의 블록이 있는지 확인하는 플래그
                if col+L>N:                                # 경사로를 놓는 범위를 벗어날 경우
                    break
                for i in range(0,L):
                    if ramp_check[col+i]==1:               #이미 경사로가 놓여있는 경우
                        wrong=1
                        break
                    ramp_check[col+i]=1
                    if board[row][col+i]!=board[row][col]:  #L 길이만큼 탐색했을때 다른 높이의 블록이 있는 경우
                        wrong=1                             #while문을 탈출하기 위한 플래그
                        break
                if wrong==1:
                    break
                previous_height=board[row][col]             #경사로를 놓은 높이로 이전 높이를 변경
                col+=L-1                                    #경사로를 놓은 높이의 다음 블록부터 탐색
                if col==N-1:
                    col_able+=1
                    break
                continue
            elif board[row][col]-previous_height==1:        #올라가는 경사로인 경우
                wrong=0                                     #L 길이만큼 탐색했을때 다른 높이의 블록이 있는지 확인하는 플래그
                if col-L<0:                                #경사로를 놓을 범위를 벗어나는 경우
                    break
                for i in range(0,L):
                    if ramp_check[col-1-i]==1:               #이미 경사로가 놓여있는 경우
                        wrong=1
                        break
                    ramp_check[col-1-i]=1
                    if board[row][col-1-i]!=board[row][col-1]:  #L 길이만큼 탐색했을때 다른 높이의 블록이 있는 경우
                        wrong=1                             #while문을 탈출하기 위한 플래그
                        break
                if wrong==1:
                    break
                previous_height=board[row][col]             #경사로를 놓은 높이로 이전 높이를 변경
                continue
            else: 
                break

        if col==N-1:
            col_able+=1
            break
        col+=1
 

row_able=0
for col in range(N):
    previous_height=board[0][col]
    row=1
    ramp_check=[0]*N
    while True:
        if board[row][col]!=previous_height:
            if previous_height-board[row][col]==1:
                wrong=0

                if row+L>N:
                    break
                for i in range(0,L):
                    if ramp_check[row+i]==1:               #이미 경사로가 놓여있는 경우
                        wrong=1
                        break
                    ramp_check[row+i]=1
                    if board[row+i][col]!=board[row][col]:  #L 길이만큼 탐색했을때 다른 높이의 블록이 있는 경우
                        wrong=1                             #while문을 탈출하기 위한 플래그
                        break
                if wrong==1:
                    break
                previous_height=board[row][col]             #경사로를 놓은 높이로 이전 높이를 변경
                row+=L-1                                    #경사로를 놓은 높이의 다음 블록부터 탐색
                if row==N-1:
                    row_able+=1
                    break
                continue

            elif board[row][col]-previous_height==1:        #올라가는 경사로인 경우
                wrong=0                                     #L 길이만큼 탐색했을때 다른 높이의 블록이 있는지 확인하는 플래그
                if row-L<0:                                #경사로를 놓을 범위를 벗어나는 경우
                    break
                for i in range(0,L):
                    if ramp_check[row-1-i]==1:               #이미 경사로가 놓여있는 경우
                        wrong=1
                        break
                    ramp_check[row-1-i]=1
                    if board[row-1-i][col]!=board[row-1][col]:  #L 길이만큼 탐색했을때 다른 높이의 블록이 있는 경우
                        wrong=1                             #while문을 탈출하기 위한 플래그
                        break
                if wrong==1:
                    break
                previous_height=board[row][col]             #경사로를 놓은 높이로 이전 높이를 변경
                continue
            else:
                break
        if row==N-1:
            row_able+=1
            break
        row+=1

print(row_able+col_able)
