#!/bin/sh

cd ~
if grep -q "export PATH+=:~/.Sudoku-Solver/" "./.bashrc"; then
	sed -i -e "s@export PATH+=:~/.Sudoku-Solver/@@g" ~/.bashrc;
fi
rm -rf ~/.Sudoku-Solver


