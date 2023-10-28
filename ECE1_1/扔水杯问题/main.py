# cup_drop() 位于 main.py 文件 第5行
# main.py


def cup_drop(k: int, n: int) -> int:
    '''
    solution to this question
    :type k: int
    :type n: int
    '''
    if n == 1:
        return 1
    f = [[0]*(k+1) for _ in range(n+1)]
    for i in range(1, k+1):
        f[1][i] = 1
    res = -1
    for i in range(2, n+1):
        for j in range(1, k+1):
            f[i][j] = 1+f[i-1][j-1]+f[i-1][j]
        if f[i][j] >= n:
            res = i
            break
    return res


if __name__ == '__main__':
    number = cup_drop(k=2, n=6)
    print(number)
    number = cup_drop(k=3, n=14)
    print(number)
