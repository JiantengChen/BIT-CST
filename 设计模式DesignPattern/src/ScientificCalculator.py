from typing import List
from math import pi, e, sin, cos, exp
import re
from numpy import deg2rad


class BigNumberCalculator:
    def __init__(self):
        self.base = 65535

    def split_big_number(self, big_num):
        a = big_num // self.base
        b = big_num % self.base
        return a, b

    def combine_big_number(self, a, b):
        return a * self.base + b

    class BigNumAdditionStrategy:
        def __init__(self, calculator):
            self.calculator = calculator

        def calculate(self, value1: float, value2: float) -> float:
            a1, b1 = self.calculator.split_big_number(value1)
            a2, b2 = self.calculator.split_big_number(value2)
            a_sum = a1 + a2
            b_sum = b1 + b2

            if b_sum >= self.calculator.base:
                a_sum += 1
                b_sum -= self.calculator.base

            print("Calling Big Num Addition.")

            return self.calculator.combine_big_number(a_sum, b_sum)

    class BigNumSubtractStrategy:
        def __init__(self, calculator):
            self.calculator = calculator

        def calculate(self, value1: float, value2: float) -> float:
            a1, b1 = self.calculator.split_big_number(value2)
            a2, b2 = self.calculator.split_big_number(value1)
            if value1 <= value2:
                a_diff = a1 - a2
                b_diff = b1 - b2

                if b_diff < 0:
                    a_diff -= 1
                    b_diff += self.calculator.base
            else:
                a_diff = a2 - a1
                b_diff = b2 - b1

                if b_diff < 0:
                    a_diff -= 1
                    b_diff += self.calculator.base

            print("Calling Big Num Subtraction.")

            return self.calculator.combine_big_number(a_diff, b_diff)

    class BigNumMultiplicationStrategy:
        def __init__(self, calculator):
            self.calculator = calculator

        def calculate(self, value1: float, value2: float) -> float:
            a1, b1 = self.calculator.split_big_number(value1)
            a2, b2 = self.calculator.split_big_number(value2)
            X = b1 * b2
            Y = a2 * b1 + a1 * b2
            Z = a1 * a2

            # 处理进位
            carry1 = X // self.calculator.base
            X %= self.calculator.base

            carry2 = (Y + carry1) // self.calculator.base
            Y = (Y + carry1) % self.calculator.base

            Z += carry2

            print("Calling Big Num Multiplication.")

            return self.calculator.combine_big_number(
                Z, self.calculator.combine_big_number(Y, X)
            )


class ScientificCalculator:
    def __init__(self):
        """define the related variable"""
        self.result = None
        self.precedence = {
            "+": 1,
            "-": 1,
            "*": 2,
            "/": 2,
            "^": 3,
            "sin": 3,
            "cos": 3,
            "!": 4,
        }
        self.sign = ["+", "-", "*", "/", "^", "(", ")", "!", "sin", "cos"]
        self.big_number_calculator = BigNumberCalculator()

    def brackets_pare(self, expression_list: List) -> bool:
        """judge whether the brackets pare

        Args:
            expression_list (List): the original expression_list

        Returns:
            bool: result
        """
        return (
            True if expression_list.count("(") == expression_list.count(")") else False
        )

    def expression_pretreatment(self, expression: str) -> List:
        """pretreat the input infix expression, dealing with "-" and "." in the expression.

        Args:
            expression (str): the infix expression

        Returns:
            List: a list follow the infix order after pretreatment
        """
        expression_opt = ""
        for i in range(len(expression)):
            if expression[i] == " ":
                continue
            elif expression[i] == "-":
                if i == 0 or expression[i - 1] == "(":
                    expression_opt += "0"
                expression_opt += " "
                expression_opt += expression[i]
                expression_opt += " "
            elif expression[i] in self.sign:
                expression_opt += " "
                expression_opt += expression[i]
                expression_opt += " "
            else:
                expression_opt += expression[i]

        expression_list = []
        for item in expression_opt.split(" "):
            if item == "e":
                expression_list.append(str(e))
            elif item == "pi":
                expression_list.append(str(pi))
            elif item != "":
                expression_list.append(item)
        return expression_list

    def postfix(self, expression_list: List) -> List:
        """transform the infix expression to the postfix expression

        Args:
            expression_list (List): a list follow the infix order after pretreatment

        Returns:
            List: return a list follow the postfix order
        """
        stack = []
        postfix = []

        for item in expression_list:
            if item == "(":
                stack.append("(")
            elif item == ")":
                while stack and stack[-1] != "(":
                    postfix.append(stack.pop())
                if stack and stack[-1] == "(":
                    stack.pop()
            elif item in self.precedence.keys():
                while (
                    stack
                    and stack[-1] != "("
                    and self.precedence.get(stack[-1], 0) >= self.precedence.get(item)
                ):
                    postfix.append(stack.pop())
                stack.append(item)
            else:
                postfix.append(item)

        while stack:
            postfix.append(stack.pop())
        return postfix

    def calculate(self, value1: float, value2: float) -> float:
        pass

    def sin(self, value1: float) -> float:
        pass

    def cos(self, value1: float) -> float:
        pass

    def exp(self, value1: float) -> float:
        pass

    def _observation(self, value1: float, observation_mode: str) -> str:
        result_map = {
            "bin": BinaryObserver(),
            "oct": OctalObserver(),
            "hex": HexadecimalObserver(),
            "dec": DecimalObserver(),
        }
        return result_map[observation_mode].update(int(value1))

    def update(self, value1: float) -> float:
        pass

    def _radian(self, value1: float) -> float:
        """convert the number into the radian

        Args:
            value1 (float): number

        Returns:
            float: the radian expression
        """
        return deg2rad(value1)

    def custom_compare(self, postfix: List) -> bool:
        base = self.big_number_calculator.base
        for item in postfix:
            try:
                if float(item) >= base:
                    return True
            except:
                continue
        return False

    def calculate_postfix(self, postfix: List) -> float:
        """calculate the result of a postfix list

        Args:
            postfix (List): a list follow the postfix order

        Returns:
            float: the calculation result
        """
        large_num_flag = True if self.custom_compare(postfix) else False
        stack_cal = []

        calculate_strategy = {
            "+": self.big_number_calculator.BigNumAdditionStrategy(
                self.big_number_calculator
            )
            if large_num_flag
            else AdditionStrategy(),
            "-": self.big_number_calculator.BigNumSubtractStrategy(
                self.big_number_calculator
            )
            if large_num_flag
            else SubtractionStrategy(),
            "*": self.big_number_calculator.BigNumMultiplicationStrategy(
                self.big_number_calculator
            )
            if large_num_flag
            else MultiplicationStrategy(),
            "/": DivisionStrategy(),
            "^": PowerStrategy(),
            "!": FactorialStrategy(),
            "sin": MathTrigonometryAdapter(),
            "cos": MathTrigonometryAdapter(),
            "exp": MathTrigonometryAdapter(),
        }
        for item in postfix:
            if item in self.precedence.keys():
                value1 = float(stack_cal.pop())
                if item not in ["!", "sin", "cos"]:
                    value2 = float(stack_cal.pop())
                    result = calculate_strategy[item].calculate(value1, value2)
                elif item == "!":
                    result = calculate_strategy[item].calculate(value1)
                elif item in ["sin", "cos"]:
                    result = getattr(calculate_strategy[item], item)(value1)
                stack_cal.append(result)
            else:
                stack_cal.append(item)

        return stack_cal.pop()


class AdditionStrategy(ScientificCalculator):
    def calculate(self, value1: float, value2: float) -> float:
        return value1 + value2


class SubtractionStrategy(ScientificCalculator):
    def calculate(self, value1: float, value2: float) -> float:
        return value2 - value1


class MultiplicationStrategy(ScientificCalculator):
    def calculate(self, value1: float, value2: float) -> float:
        return value1 * value2


class DivisionStrategy(ScientificCalculator):
    def calculate(self, value1: float, value2: float) -> float:
        return value2 / value1


class PowerStrategy(ScientificCalculator):
    def calculate(self, value1: float, value2: float) -> float:
        return value2**value1


class FactorialStrategy(ScientificCalculator):
    def calculate(self, value1: float) -> float:
        if value1 == 0:
            return 1
        else:
            return value1 * self.calculate(value1 - 1)


class MathTrigonometryAdapter(ScientificCalculator):
    def sin(self, value1: float) -> float:
        return sin(value1)

    def cos(self, value1: float) -> float:
        return cos(value1)

    def exp(self, value1: float) -> float:
        return exp(value1)


class DecimalObserver(ScientificCalculator):
    def update(self, value1):
        return value1


class BinaryObserver(ScientificCalculator):
    def update(self, value1):
        return bin(value1)


class OctalObserver(ScientificCalculator):
    def update(self, value1):
        return oct(value1)


class HexadecimalObserver(ScientificCalculator):
    def update(self, value1):
        return hex(value1)
