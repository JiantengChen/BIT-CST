# getPath.py

import os

import fire

up_path = str(os.path.dirname(os.path.dirname(os.path.realpath(__file__))))


def get_trace(trace="{}\\test.png".format(up_path)):
    return trace


path = fire.Fire(get_trace)
