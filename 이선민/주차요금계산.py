import math

def convertToMin(time):
    hour, minu = map(int, time.split(":"))
    return hour * 60 + minu
    
def getTotalTime(start, end):
    startMin = convertToMin(start)
    endMin = convertToMin(end)
    return endMin - startMin

def getPrice(time, fees):
    defaultTime, defaultFee, unitTime, unitFee = fees
    if time <= defaultTime:
        return defaultFee
    else:
        time -= defaultTime
        return defaultFee + math.ceil(time/unitTime) * unitFee        
    
    
def solution(fees, records):
    totalTimeDic = {}
    timeDic = {}
    # 누적 시간 계산
    for record in records:
        time, num, inout = record.split(" ")
        if inout == "IN":
            timeDic[num] = time
        elif inout == "OUT":
            totalTime = getTotalTime(timeDic[num], time)
            prev = totalTimeDic.get(num, 0)
            totalTimeDic[num] = prev+totalTime
            del timeDic[num]
    for num, time in timeDic.items():
        totalTime = getTotalTime(time, "23:59")
        prev = totalTimeDic.get(num, 0)
        totalTimeDic[num] = prev+totalTime
    # 차량번호 순 정렬
    result = []
    for num, totalTime in totalTimeDic.items():
        result.append((num, totalTime))
    result.sort(key=lambda x: x[0])
    
    # 주차요금 계산한 결과 담은 배열 반환
    return [getPrice(totalTime, fees) for num, totalTime in result]