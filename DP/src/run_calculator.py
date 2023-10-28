from gui import Calculator
import sys
from PyQt5.QtWidgets import QApplication
import argparse
from test_demonstrator import demonstrator


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="""
        select running mode of Calculator
                                     """
    )
    parser.add_argument(
        "--tests",
        "-t",
        metavar="",
        type=str,
        default="0",
        help="run the calculator with tests results or not",
    )
    args = parser.parse_args()
    tests = eval(args.tests)
    if tests:
        demonstrator()
    app = QApplication(sys.argv)
    calculator = Calculator()
    calculator.show()
    sys.exit(app.exec_())
