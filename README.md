# Project 2

To compile the program type: make

Flag options
- Help Screen (this): -H
- Debugging: -D
- Run All Tests: -T
- Run All Tests with results printed to screen (n for Noisy): -T n
- Run with inputFile: relative/path/to/file

To run for memory leaks,
valgrind -v --track-origins=yes --show-leak-kinds=all --leak-check=full --log-file=logs/valgrind.log ./project2Ex -T n
