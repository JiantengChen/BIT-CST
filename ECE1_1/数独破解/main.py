# main.py


import numpy as np





def matrix_input():
    '''
    手动输入模式下输入数独初盘
    '''
    shape = (9, 9)
    matrix_input = np.zeros(shape, int)
    print("请输入数独初盘,以9*9的数字矩阵表示,其中0表示表示该位置无数字")
    print("依次输入每一行的数字,数字与数字之间用空格分隔,输入完成后敲击回车:")
    for i in range(9):
        # a = input("第{}行: ".format(i+1))
        a = input()
        a = a.split()
        matrix_input[i] = a
    return matrix_input


def sudoku(matrix_input):
    '''
    数独破解算法
    '''
    matrix_output = matrix_input
    line = [set(range(1, 10)) for _ in range(9)]
    column = [set(range(1, 10)) for _ in range(9)]
    block = [set(range(1, 10)) for _ in range(9)]
    spaces = []

    for i in range(9):
        for j in range(9):
            if matrix_output[i][j] != 0:
                val = matrix_output[i][j]
                line[i].remove(val)
                column[j].remove(val)
                block[(i//3)*3+j//3].remove(val)
            else:
                spaces.append((i, j))

    def recall(count=0):
        if count == len(spaces):
            return True
        i, j = spaces[count]
        b = (i//3)*3+j//3
        for val in line[i] & column[j] & block[b]:
            line[i].remove(val)
            column[j].remove(val)
            block[b].remove(val)
            matrix_output[i][j] = val
            if recall(count+1):
                return True
            line[i].add(val)
            column[j].add(val)
            block[b].add(val)
        return False

    recall()
    return matrix_output


def main():
    case = input("请选择\n1.手动输入数独矩阵\n2.文件读取\n输入数字并回车:\n")
    if case =='1':
        matrix_output = sudoku(matrix_input())
    elif case =='2':
        f = open("sudoku.txt",'r',encoding='utf-8')
        board = f.read().replace('\n',' ')
        board = board.split(' ')
        board = np.array(board)
        matrix_input_2 =[]
        for item in board:
            matrix_input_2.append(eval(item))
        board = np.resize(matrix_input_2,(9,9))
        matrix_output = sudoku(board)
    print(matrix_output)

if __name__ == "__main__":
    main()