# 自动寻路 位于pathfinding.py文件 第22行
import json
from snake import Snake
from food import Food
from path_basic import PathSolve
import copy
import random


class GreedySolver:
    def __init__(self, snake, food, config):
        self.snake = copy.deepcopy(snake)
        self.food = copy.deepcopy(food)
        self.pathsolver = PathSolve(snake, food, config)
        self.config = config
        width = int(config['window-width'])
        height = int(config['window-height'])
        blk = int(config['block-size'])
        self.width = int(width / blk)
        self.height = int(height / blk)

    def nextDirection(self):
        '''
        自动寻路
        '''
        # step 1: compute shortest path
        hasPath, shortestPath = self.pathsolver.shortest_path_food()
        if hasPath:
            # step 2: move virtual snake to the food
            virtual_snake = copy.deepcopy(self.snake)
            virtual_snake.eatFood()
            for d in shortestPath:
                virtual_snake.turn(d)
                virtual_snake.next()
            # step 3: compute the longest from virtual snake head to tail
            virtual_pather = PathSolve(virtual_snake, self.food, self.config)
            has_longest_path_tail, _ = virtual_pather.longest_path_tail()
            if has_longest_path_tail:
                # ok, great.
                return shortestPath[0]
            else:
                # step 4: no, I can not eat it.
                hp3, lp3 = self.pathsolver.longest_path_tail()
                if hp3:
                    return lp3[0]
                # else, to case 5
        else:
            # step 4. compute longest from head to tail
            hp3, lp3 = self.pathsolver.longest_path_tail()
            if hp3:
                return lp3[0]
            # else, to case 5

        # worst case, case 5
        for i in range(10):
            x = random.randint(0, self.width - 1)
            y = random.randint(0, self.height - 1)
            while (x, y) in self.snake.snakebody:
                x = random.randint(0, self.width - 1)
                y = random.randint(0, self.height - 1)
            hp_w, lp_w = self.pathsolver.longest_path((x, y))
            if hp_w:
                return lp_w[0]
        return 'U'
