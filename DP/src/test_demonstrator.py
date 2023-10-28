from prettytable import PrettyTable
from math import pi, e, sin, cos
import random
import math
from ScientificCalculator import ScientificCalculator
import csv
from typing import List


def generate() -> List:
    """generate the evaluate equation

    Returns:
        List: the equation list
    """
    random.seed(0x7C)
    equations = []
    for _ in range(300):
        num1 = round(random.uniform(0, 100), 2)  # 随机生成第一个小数
        num2 = round(random.uniform(0, 100), 2)  # 随机生成第二个小数
        operator = random.choice(
            ["+", "-", "*", "/", "**", "sqrt", "cubert", "exp", "sin", "cos"]
        )  # 随机选择操作符
        if operator == "+":
            result = round(num1 + num2, 2)
            equation = f"{num1} + {num2} = "
        elif operator == "-":
            if num1 > 60 or num2 > 60:
                if num1 > num2:
                    num1, num2 = num2, num1
                else:
                    num1, num2 = num1, num2
            result = round(num1 - num2, 2)
            equation = f"{num1} - {num2} = "
        elif operator == "*":
            result = round(num1 * num2, 2)
            equation = f"{num1} * {num2} = "
        elif operator == "/":
            result = round(num1 / num2, 2)
            equation = f"{num1} / {num2} = "
        elif operator == "**":
            result = round(num1**num2, 2)
            equation = f"{num1} ** {num2} = "
        elif operator == "sqrt":
            result = round(math.sqrt(num1), 2)
            equation = f"({num1}**{0.5}) = "
        elif operator == "cubert":
            result = round(math.sqrt(num1), 2)
            equation = f"({num1}**{1.0/3}) = "
        elif operator == "exp":
            result = round(math.exp(num1), 2)
            equation = f"e^({num1}) = "
        elif operator == "sin":
            num1 = round(random.uniform(0, 30), 2)
            result = round(math.sin(num1), 2)
            equation = f"sin({num1}) = "
        elif operator == "cos":
            num1 = round(random.uniform(0, 30), 2)
            result = round(math.cos(num1), 2)
            equation = f"cos({num1}) = "
        equations.append(equation.rstrip())
    return equations


def demonstrator() -> None:
    """demonstrate the result"""
    equations = generate()
    table = PrettyTable(["No.", "equation", "output", "expectation", "result"])
    count = 0
    csv_file = "test_results\\table_data.csv"
    ac_count = 0
    with open(csv_file, "w", newline="", encoding="utf-8") as file:
        writer = csv.writer(file)
        for item in equations:
            count += 1
            expect = eval(item[:-1].replace("^", "**"))
            cal = ScientificCalculator()
            test = cal.calculate_postfix(
                cal.postfix(cal.expression_pretreatment(item[:-1].replace("**", "^")))
            )
            result = test == expect
            if result:
                ac_count += 1
            table.add_row([count, item, test, expect, result])
            data = [str(element) for element in [count, item, test, expect, result]]
            writer.writerow(data)
    accuracy = ac_count / count
    print(table)
    print(f"Accuracy: {accuracy}")
