import pygame
import json
import timeit
import time
from pathfinding import GreedySolver
from snake import Snake
from drawer import SnakeDrawer
from drawer import FoodDrawer
from food import Food
from path_basic import PathSolve

if __name__ == '__main__':
    jsdt = None
    with open('config.json', 'r') as f:
        jsdt = json.load(f)
    WIDTH = int(jsdt['window-width'])
    HEIGHT = int(jsdt['window-height'])
    BLK = int(jsdt['block-size'])
    # BLK means block
    WID_BLK = WIDTH / BLK
    HEI_BLK = HEIGHT / BLK
    if WIDTH % BLK != 0 or HEIGHT % BLK != 0:
        raise Exception(
            'Error block-size should divide window-width and window-height')
    SPEED = float(jsdt['speed'])
    AUTO = bool(jsdt['auto'])

    pygame.init()

    pygame.display.set_caption('贪吃蛇')
    screen = pygame.display.set_mode((WIDTH, HEIGHT))
    screen.fill((255, 255, 255))
    pygame.display.flip()

    snake = Snake()
    snakedrawer = SnakeDrawer(screen, jsdt, snake)
    food = Food(jsdt)
    fooddrawer = FoodDrawer(screen, jsdt, food)

    while snake.at(food.where()):
        food.generate()

    snakedrawer.draw()
    fooddrawer.draw()

    running = True
    beg_time = timeit.default_timer()
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

        now_time = timeit.default_timer()
        if now_time - beg_time >= SPEED:
            beg_time = now_time

            if AUTO:
                solver = GreedySolver(snake, food, jsdt)
                d = solver.nextDirection()
                snake.turn(d)

            # check eat food
            if snake.nextHead() == food.where():
                fooddrawer.remove()
                snake.eatFood()
                while snake.at(food.where()) or snake.nextHead() == food.where():
                    food.generate()  # TODO:

            snakedrawer.next()
            fooddrawer.draw()
            if not snake.valid():
                running = False
            x, y = snake.head()
            if x < 0 or x >= WID_BLK or y < 0 or y >= HEI_BLK:
                running = False
            pygame.display.flip()

