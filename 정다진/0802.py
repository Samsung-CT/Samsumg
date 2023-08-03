from copy import deepcopy
from collections import deque

dx = [0, 0, 1, -1]
dy = [1, -1, 0, 0]

N = int(input())

room = [list(map(int, input().split())) for _ in range(N)]

ans = []
for _ in range(4):
    now_score=0
    visited=[[0]*N for _ in range(N)]
    group=[set(())]
    group_face=[[]]
    group_num=[0]
    group_now=[0]
    cnt = 1
    for x in range(N):
        for y in range(N):
            if visited[x][y] == 0:
                q = deque()
                q.append((x,y))
                now=room[x][y]
                visited[x][y]=cnt
                face=[]
                n_g=set()
                n_g.add((x,y))
                while q:
                    px,py=q.popleft()

                    for d in range(4):
                        nx=px+dx[d]
                        ny=py+dy[d]

                        if nx<0 or nx>=N or ny<0 or ny>=N:
                            continue
                        if room[nx][ny]!=now:
                            #처음에는 set를 집합으로 해두었는데
                            #만약 이미 있는 면을 넣으면 선분이 2개가 되더라도 하나가 카운트
                            #그래서 리스트로 바뀌면, 중복은 생긱더라도
                            #한 면에서 각각 들어오는 케이스를 고려하게 됨.
                            face.append((nx,ny))
                            continue

                        if visited[nx][ny]!=0:
                            continue

                        visited[nx][ny]=cnt
                        q.append((nx,ny))
                        n_g.add((nx,ny))

                cnt+=1
                group.append(n_g)
                group_num.append(len(n_g))
                group_now.append(now)
                group_face.append(face)
    for i in range(1,len(group)):
        now_group=group[i]
        ax,ay=0,0
        for px,py in now_group:
            ax,ay=px,py
            break
        a_num=room[ax][ay]
        a_len=len(now_group)
        f_num=[0]*len(group)
        for fx,fy in group_face[i]:
            f_g=visited[fx][fy]
            f_num[f_g]+=1


        for k in range(i,len(f_num)):
            if f_num[k]==0:
                continue
            b_num=group_now[k]
            b_len=group_num[k]

            score=(a_len+b_len)*a_num*b_num*f_num[k]
            # print(a_len,a_num,b_len,b_num,f_num[k],score)
            now_socre+=score

    #print(now_socre)
    ans.append(now_socre)


mx = N // 2
my = N // 2
new_room = deepcopy(room)

# 가운데 돌리기
for y in range(my):
    new_room[N-1-y][my] = room[mx][y]

for x in range(N-1, mx, -1):
    new_room[mx][x] = room[x][my]

for y in range(N-1, my, -1):
    new_room[N-1-y][my] = room[mx][y]

for x in range(mx):
    new_room[mx][x] = room[x][my]

# 90도 회전
for x in range(mx):
    for y in range(my):
        new_room[y][my-x-1] = room[x][y]

for x in range(mx):
    for y in range(my+1, N):
        new_room[y-my-1][N-x-1] = room[x][y] 

for x in range(mx+1, N):
    for y in range(my):
        new_room[mx+1+y][N-x-1] = room[x][y]    

for x in range(mx+1, N):
    for y in range(my+1, N):
        new_room[N-my+y-N // 2 -1][N+mx-x] = room[x][y]

room = deepcopy(new_room)

print(sum(ans))