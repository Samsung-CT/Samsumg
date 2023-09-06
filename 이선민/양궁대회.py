from itertools import combinations_with_replacement

def solution(n, info):
    info.reverse()
    scores = [0,1,2,3,4,5,6,7,8,9,10]
    # 라이언이 맞춘 점수의 경우의 수
    result = combinations_with_replacement(scores, n)
    ans = []
    maxScore = 0
    for res in result:
        # 라이언이 맞춘 점수 info랑 같은 형식의 배열로 변경
        lion = [0] * 11
        tmp = list(res)
        for score in tmp:
            lion[score] += 1
        # 라이언과 어피치 각각 토탈 점수 계산
        lionTotal = 0
        apeachTotal = 0
        for score in scores:
            a = info[score]
            l = lion[score]
            if l == a == 0:
                continue
            if l > a:
                lionTotal += score
            else:
                apeachTotal += score
        # 라이언이 우승했는지 여부 체크해서 ans에 반영
        lion.reverse()
        if lionTotal - apeachTotal > maxScore:
            ans.clear()
            ans.append(lion)
            maxScore = lionTotal - apeachTotal
        if lionTotal - apeachTotal == maxScore:
            ans.append(lion) 
    # 라이언이 우승할 방법이 없으면 -1 리턴
    if maxScore == 0:
        return [-1]
    # 라이언이 우승할 수 있는 경우, 가장 낮은 점수를 더 많이 맞힌 경우 리턴
    ans.sort(reverse=True, key=lambda x:(x[10],x[9],x[8],x[7],x[6],x[5],x[4],x[3],x[2],x[1],x[0]))
    return ans[0]