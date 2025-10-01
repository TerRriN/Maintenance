# Giant Sudoku Solver
This Sudoku solver can solve puzzles of various **SYMETRICAL** sizes. It uses logic based possibility elimination and backtracking bruteforce to solve the puzzle. The solver is able to solve puzzles as large as your hardware allows (stack overflow is a real issue).

__Note:__ The solution time varies heavily on the input puzzle. The solver is able to solve most puzzles in a reasonable time frame. However, some puzzles may take a long time to solve. It all depends on how many cells the solver needs to bruteforce and how many possibilities are available for each cell.

## Usage
The solver is written in C. A makefile is provided to compile the solver. The solver can run with the following commands:  
To compile the solver:
```bash
make
```
Run solver:
```
./sudoku <INPUT PATH> <BOARD SZIE> <N THREADS>
EX: ./sudoku input/txt25/6x25.txt 25 4
```
See makefile for more examples.

### Performance
To run performance tests on an entire folder use the provided shellscript. Runs on 4 threads by default. 
```
scripts/./run-sudoku.sh <BOARD SIZE> <N THREADS (OPTIONAL)>
EX: scripts/./run-sudoku.sh 9
    or
    scripts/./run-sudoku.sh 9 16
```
__Note:__ A lot of print statements can be turned on/off in the main.c file, by changing the "DEMO" variable (line 21) to 0.

### Demo
To see a live demonstration of the bruteforce algorithm:
```
make runDemo9
```
See makefile for more examples.
__Note:__ the demo version is NOT threaded. If you get EARLY SOLUTION, remove eliminate_possibilities(). 

## Input
Input files can be in the format of .txt. If you whish to use your own input data, see input files for examples. Make sure the puzzle is symetrical and the puzzle only has one solution. Easiest way to create a puzzle is to copy one from the web, write a translator that converts the puzzle to the correct format, and save it as a .txt file. The input reader is very tricky and cannot handle a single typo or missplaced space.

Other sites which I used to generate puzzles:
[sudoku-download.net](http://www.sudoku-download.net/sudoku_64x64.php)
[sudokugeant.cabanova.com](https://sudokugeant.cabanova.com/sudoku.html)

## Output
The solver will output one of three statements:
- EARLY SOLUTION __- If the puzzle was solved before the bruteforce was needed__
- SOLUTION __- If the puzzle was solved__
- NO SOLUTION __- If the puzzle was not solved__

The solver will print the solved puzzle to the terminal if the "DEMO" variable is set to 1. The solver will also print the time it took to solve the puzzle.
