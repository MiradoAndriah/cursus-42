#!/usr/bin/env python3
import random

NORTH = 1
EAST = 2
SOUTH = 4
WEST = 8

class MazeGenerator:
    def __init__(self, width, height, entry, exit, seed):
        self.width = width
        self.height = height
        self.entry = entry
        self.exit = exit
        self.seed = seed
        random.seed(seed)
        self.grid = [[15 for x in range(self.width)] for y in range(self.height)]
        self.visited = [[False for x in range(self.width)] for y in range(self.height)]
        
    def generate(self):
        x = self.entry[0]
        y = self.entry[1]
        self.visited[y][x] = True
        stack = [(x, y)]
        while stack:
            last = stack[-1]
            x = last[0]
            y = last[1]
            unvisited_voisin = self.get_unvisited_voisin(x, y)
            if unvisited_voisin:
                voisin = random.choice(unvisited_voisin)
                next_x = voisin[0]
                next_y = voisin[1]
                direction = voisin[2]
                self.visited[next_y][next_x] = True
                stack.append((next_x, next_y))
                self.join_wall(x, y, next_x, next_y, direction)
            else:
                stack.pop()

    def get_unvisited_voisin(self, x, y):
        voisins = []
        if y - 1 >= 0 and self.visited[y - 1][x] == False:
            voisins.append((x, y - 1, NORTH))
        if x + 1 < self.width and self.visited[y][x + 1] == False:
            voisins.append((x + 1, y, EAST))
        if y + 1 < self.height and self.visited[y + 1][x] == False:
            voisins.append((x, y + 1, SOUTH))
        if x - 1 >= 0 and self.visited[y][x - 1] == False:
            voisins.append((x - 1, y, WEST))
        return voisins
    
    def join_wall(self, x, y, nx, ny, direction):
        if direction == NORTH:
            self.grid[y][x] &= ~NORTH
            self.grid[ny][nx] &= ~SOUTH
        elif direction == EAST:
            self.grid[y][x] &= ~EAST
            self.grid[ny][nx] &= ~WEST
        elif direction == SOUTH:
            self.grid[y][x] &= ~SOUTH
            self.grid[ny][nx] &= ~NORTH
        elif direction == WEST:
            self.grid[y][x] &= ~WEST
            self.grid[ny][nx] &= ~EAST

    def get_grid(self):
        return self.grid
    
    def get_solution(self):
        


if __name__ == "__main__":
    maze = MazeGenerator(5, 5, (0, 0), (4, 4), 42)
    maze.generate()
    for row in maze.grid:
        print(row)