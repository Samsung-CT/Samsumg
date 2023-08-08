import sys
from collections import deque

input = sys.stdin.readline

diceNums = list(map(int, input().split(" ")))

players = [0,0,0,0]
scores = [0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,0,13,16,19,25,26,27,28,30,35,24,22]
firstBlueRoute = [5, 22,23,24,25,29,30,20,21]
secondBlueRoute = [10, 32, 31, 25, 29, 30,20,21]
thirdBlueRoute = [15,28,27,26,25,29,30,20,21]


def movePlayer(player, dice, othersPosition):
    position, score = player
    if (position==21): return [position, score]
    newPosition = position + dice if position + dice < 22 else 21
    if position in firstBlueRoute:
        tmp = firstBlueRoute.index(position)+dice
        if tmp >= len(firstBlueRoute): newPosition = 21
        else: newPosition = firstBlueRoute[tmp]
    elif position in secondBlueRoute:
        tmp = secondBlueRoute.index(position)+dice
        if tmp >= len(secondBlueRoute): newPosition = 21
        else: newPosition = secondBlueRoute[tmp]
    elif position in thirdBlueRoute:
        tmp = thirdBlueRoute.index(position)+dice
        if tmp >= len(thirdBlueRoute): newPosition = 21
        else: newPosition = thirdBlueRoute[tmp]
    if newPosition in othersPosition and newPosition != 21:
        return 0
    return [newPosition, score+scores[newPosition]]



def solution():
    q = deque()
    # [게임턴, 각 말 정보]
    # 말번호: [말 위치, 현재 해당 말 점수]
    q.append([0, [
        [0, 0],
        [0, 0],
        [0, 0],
        [0, 0]
    ]])
    result = 0
    while q:
        turn, player = q.popleft()
        one, two, three, four = player
        # print(turn)
        if turn == 10:
            if result < one[1]+two[1]+three[1]+four[1]:
                result = one[1]+two[1]+three[1]+four[1]
            continue
        # 말 움직이기
        tmp = movePlayer(one, diceNums[turn], [two[0], three[0], four[0]])
        if tmp != 0:
            q.append([turn+1, [tmp, two, three, four]])
        tmp = movePlayer(two, diceNums[turn], [one[0], three[0], four[0]])
        if tmp != 0:
            q.append([turn+1, [one, tmp, three, four]])
        tmp = movePlayer(three, diceNums[turn], [two[0], one[0], four[0]])
        if tmp != 0:
            q.append([turn+1, [one, two, tmp, four]])
        tmp = movePlayer(four, diceNums[turn], [two[0], three[0], one[0]])
        if tmp != 0:
            q.append([turn+1, [one, two, three, tmp]])
    # print(result)
    return result

print(solution())