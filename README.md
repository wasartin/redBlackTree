# Project 2

Flag options
\t Help Screen (this): -H
\t Debugging: -D
\t Run All Tests: -T n
\t Run with inputFile: path/to/file

To run for memory leaks,
valgrind -v --track-origins=yes --show-leak-kinds=all --leak-check=full --log-file=logs/valgrind.log ./project2Ex -T n
