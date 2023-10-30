# 数独破解项目解读
## 项目介绍
- 由文件读取数独初盘（9*9数字矩阵，0表示空格），在标准输出处展示求解结果
- 项目考察重点集中在求解算法， 大家主要关注求解速度和能够出解的数独难度（空格数）
## 运行方法
- 运行主程序main.py，根据文字提示选择手动输入矩阵或从文件读取
- 数独初盘以9*9的数字矩阵表示，其中0表示表示该位置无数字
- 如选择**手动输入**，依次输入每一行的数字，数字与数字之间用空格分隔，输入完成后敲击回车
- 如选择**文件读取**，则在文件中存放9行的数字矩阵，数字与数字之间用空格分隔
## 算法介绍
### 代码展示
```python
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
```
### 算法详解
**本次数独破解问题采用了递归+回溯的算法，但对于不同的输入数据，算法复杂度也随之改变，并且无法准确逼近，但相比于传统的暴力枚举，仍拥有不错的计算速度**
***
**思路**

- 数独破解满足三个约束条件，分别是每一列不能重复，每一行不能重复，每一宫不能重复，故设想通过Boolean类型记录是否出现
- 利用python中set集合的去重性质来实现记录一个数字是否实现  

**算法**
1. 遍历数组，如果是空白格，则将其存储到一个列表中，方便后续递归
2. 遍历数组，如果是数字，则在该数字对应的行、列和宫格数字的集合中利用set中remove函数删去该数字
3. 遍历存储空白格的列表，从上述三个集合中进行与运算，选取available的数字进行尝试
4. 在三个集合中remove上述填入空白格的数字，对下一空白格进行运算  
**3、4两步即为递归**
5. 如果递归过程中有空格无法通过available的数字满足约束条件，则向前回溯到上一空白格，将4中remove的数字add回集合中，再选取下一满足条件的数字进行运算  
**第5步为回溯**
6. 跳出递归的条件为递归次数等于存储空白格的列表长度，防止再次运算，覆盖原有运算结果