#!/bin/sh

gcc solver.c -o SDS
cd ~
if find -name "Sudoku-Solver" | grep -q "~/Sudoku-Solver"; then
	mv ~/Sudoku-Solver ~/.Sudoku-Solver
fi
if ! grep -q "export PATH+=:~/.Sudoku-Solver/" "./.bashrc"; then
	echo "export PATH+=:~/.Sudoku-Solver/" >> ~/.bashrc;
fi
bash

