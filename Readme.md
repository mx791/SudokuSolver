# Simple Sudoku Solver
Using c++ to auto-solve sudoku grid.

## Input
You can add your uncomplete grid in the `grid.txt` file. The grid should match the following format:
```
0 0 0 5 8 0 7 0 0
0 9 7 0 0 0 0 0 1
0 0 0 0 6 7 0 9 0
0 0 1 0 9 0 0 0 5
0 0 2 0 0 0 0 0 0
0 0 0 0 4 0 0 0 0
0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 3 8 0
0 0 0 0 0 0 0 0 0
```
All values should be separeted with a space.
The grid's size should be 4 or 9.

## Output
Once it's done, the programm should output the following :
```
iters: 2585
1 2 3 5 8 9 7 4 6
6 9 7 2 3 4 8 5 1
4 5 8 1 6 7 2 9 3
3 4 1 7 9 8 6 2 5
7 8 2 6 1 5 4 3 9
5 6 9 3 4 2 1 7 8
2 1 5 8 7 3 9 6 4
9 7 6 4 5 1 3 8 2
8 3 4 9 2 6 5 1 7
```
In case the grid isn't solvable, an error message will be displayed.

## Running
```
g++ -o main sudoku.cpp
main
```