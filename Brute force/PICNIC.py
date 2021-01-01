answer = []


def calAns(pairList, numList):
    result = 0

    if not numList:
        return 1
    elif not pairList:
        return 0

    if pairList[0][0] in numList and pairList[0][1] in numList:
        temp = pairList.pop(0)

        result += calAns(pairList, numList)

        numList.remove(temp[0])
        numList.remove(temp[1])
        result += calAns(pairList, numList)

        numList.insert(0, temp[0])
        numList.insert(0, temp[1])
        pairList.insert(0, temp)
        return result
    else:
        temp = pairList.pop(0)
        result = calAns(pairList, numList)
        pairList.insert(0, temp)
        return result


case = int(input())
for i in range(0, case):
    num, pairNum = input().split()
    num = int(num)
    pairNum = int(pairNum)

    pairList = []
    numList = [x for x in range(num)]
    first, second = (0, 0)
    pairInputList = [int(x) for x in input().strip().split()]

    while pairInputList:
        pairList.append((pairInputList.pop(0), pairInputList.pop(0)))

    answer.append(calAns(pairList, numList))


for i in range(0, len(answer)):
    print(answer[i])

