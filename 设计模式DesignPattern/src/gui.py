from PyQt5.QtGui import QFont
from PyQt5.QtWidgets import QWidget, QLineEdit, QPushButton, QGridLayout
from ScientificCalculator import ScientificCalculator


def add_superscript(text) -> str:
    """optimize the ui

    Args:
        text (str): string

    Returns:
        string: result
    """
    superscript_mapping = str.maketrans(
        "0123456789+-=()abcdefghijklmnopqrstuvwxyzAB",
        "⁰¹²³⁴⁵⁶⁷⁸⁹⁺⁻⁼⁽⁾ᵃᵇᶜᵈᵉᶠᵍʰⁱʲᵏˡᵐⁿᵒᵖᵠʳˢᵗᵘᵛʷˣʸᶻ½⅓",
    )
    return text.translate(superscript_mapping)


class Calculator(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Scientific Calculator")
        self.special_sign = {
            "e" + add_superscript("x"): "e^",
            "x" + add_superscript("2"): "^2",
            "x" + add_superscript("A"): "^(1.0/2)",
            "x" + add_superscript("3"): "^3",
            "x" + add_superscript("B"): "^(1.0/3)",
            "x" + add_superscript("y"): "^",
        }
        self.triangle_sign = {"sin": "sin", "cos": "cos"}
        self.sign = ["+", "-", "*", "/", "^", "(", ")", "!", "sin", "cos"]

        self.resize(800, 600)
        self.line_edit = QLineEdit(self)
        self.line_edit.setReadOnly(True)
        self.buttons = [
            "C",
            "RAD",
            "!",
            "Backspace",
            "7",
            "8",
            "9",
            "/",
            "4",
            "5",
            "6",
            "*",
            "1",
            "2",
            "3",
            "-",
            "0",
            ".",
            "=",
            "+",
            "(",
            ")",
            "sin",
            "cos",
            "e" + add_superscript("x"),
            "x" + add_superscript("2"),
            "x" + add_superscript("A"),
            "x" + add_superscript("3"),
            "x" + add_superscript("B"),
            "x" + add_superscript("y"),
            "e",
            "pi",
            "bin",
            "hex",
            "oct",
            "dec",
        ]

        layout = QGridLayout()
        self.line_edit.setFixedHeight(150)
        font = QFont("Arial", 32)
        self.line_edit.setFont(font)
        layout.addWidget(self.line_edit)
        button_style = """
        QPushButton {
            background-color: #D3D3D3;
            border: none;
            color: black;
            font: Arial;
            font-size: 36px;
            height: 100;
            width: 180;
            border-style: outset;
            border: 2px solid #778899
        }

        QPushButton:hover {
            background-color: #45a049;
        }        
        """
        for button_text in self.buttons:
            button = QPushButton(button_text)
            button.setStyleSheet(button_style)
            # button.setStyleSheet()
            button.clicked.connect(self.button_clicked)
            layout.addWidget(button)

        layout = QGridLayout()
        layout.addWidget(self.line_edit, 0, 0, 2, 4)

        row = 3
        col = 0
        for button_text in self.buttons:
            button = QPushButton(button_text)
            button.setStyleSheet(button_style)
            button.clicked.connect(self.button_clicked)
            layout.addWidget(button, row, col)
            col += 1
            if col > 3:
                col = 0
                row += 1

        self.setLayout(layout)

    def button_clicked(self):
        """button_clicked"""
        if self.line_edit.text() == "Error":
            self.line_edit.clear()
        button = self.sender()
        text = button.text()
        if text == "=":
            try:
                infix_expression = self.line_edit.text()
                cal = ScientificCalculator()
                res = cal.calculate_postfix(
                    cal.postfix(cal.expression_pretreatment(infix_expression))
                )
                self.line_edit.setText(str(res))
            except:
                self.line_edit.setText("Error")
        elif text == "RAD":
            try:
                temp_string = self.line_edit.text()
                res_string = ScientificCalculator()._radian(eval(temp_string))
                self.line_edit.setText(str(res_string))
            except:
                self.line_edit.setText("Error")
        elif text in ["bin", "hex", "oct", "dec"]:
            try:
                temp_string = self.line_edit.text()
                res_string = ScientificCalculator()._observation(
                    eval(temp_string), text
                )
                self.line_edit.setText(str(res_string))
            except:
                self.line_edit.setText("Error")
        elif text == "C":
            self.line_edit.clear()
        elif text == "Backspace":
            self.line_edit.backspace()
        elif text == "e" + add_superscript("x"):
            try:
                list_temp = ScientificCalculator().expression_pretreatment(
                    expression=self.line_edit.text()
                )
                last_word = list_temp[-1]
                length_str = len(list_temp)
                if isinstance(eval(last_word), float) or isinstance(
                    eval(last_word), int
                ):
                    list_temp.insert(-1, self.special_sign[text])
                    return_str = "".join(list_temp)
                    self.line_edit.setText(return_str)
                elif last_word == ")":
                    for i in range(length_str):
                        if list_temp[length_str - i - 1] == "(":
                            list_temp.insert(
                                length_str - i - 1, self.special_sign[text]
                            )
                            break
                    return_str = "".join(list_temp)
                    self.line_edit.setText(return_str)
                elif last_word == "!":
                    for i in range(length_str - 1):
                        if list_temp[length_str - i - 1] != "!" and (
                            list_temp[length_str - i - 1] in self.sign
                            or length_str - i - 1 == 0
                        ):
                            list_temp.insert(
                                length_str - i - 1, self.special_sign[text]
                            )
                            break
                    return_str = "".join(list_temp)
                    self.line_edit.setText(return_str)
                else:
                    self.line_edit.setText("Error")
            except:
                self.line_edit.setText("Error")
        elif text in self.special_sign.keys():
            try:
                list_temp = ScientificCalculator().expression_pretreatment(
                    expression=self.line_edit.text()
                )
                last_word = list_temp[-1]
                if (
                    isinstance(eval(last_word), float)
                    or isinstance(eval(last_word), int)
                    or last_word == ")"
                    or last_word == "!"
                ):
                    list_temp.append(self.special_sign[text])
                    return_str = "".join(list_temp)
                    self.line_edit.setText(return_str)
                else:
                    self.line_edit.setText("Error")
            except:
                self.line_edit.setText("Error")
        elif text in self.triangle_sign.keys():
            list_temp = ScientificCalculator().expression_pretreatment(
                expression=self.line_edit.text()
            )
            try:
                last_word = list_temp[-1]
                length_str = len(list_temp)
                if isinstance(eval(last_word), float) or isinstance(
                    eval(last_word), int
                ):
                    list_temp.insert(-2, self.triangle_sign[text])
                    list_temp.insert(-1, "(")
                    list_temp.append(")")
                    return_str = "".join(list_temp)
                    self.line_edit.setText(return_str)
                elif last_word == "!":
                    for i in range(length_str - 1):
                        if list_temp[length_str - i - 1] != "!" and (
                            list_temp[length_str - i - 1] in self.sign
                            or length_str - i - 1 == 0
                        ):
                            list_temp.insert(
                                length_str - i - 1, self.triangle_sign[text]
                            )
                            break
                    return_str = "".join(list_temp)
                    self.line_edit.setText(return_str)
                elif last_word == ")":
                    for i in range(length_str):
                        if list_temp[length_str - i - 1] == "(":
                            list_temp.insert(
                                length_str - i - 1, self.triangle_sign[text]
                            )
                            break
                    return_str = "".join(list_temp)
                    self.line_edit.setText(return_str)
                else:
                    self.line_edit.setText("Error")
            except:
                self.line_edit.setText("Error")
        else:
            self.line_edit.setText(self.line_edit.text() + text)
