#!/bin/sh

cd ~
if grep -q "export PATH+=:~/.Sudoku-Destroyer/" "./.bashrc"; then
	sed -i -e "s@export PATH+=:~/.Sudoku-Destroyer/@@g" ~/.bashrc;
else echo "既にPATHはありません"
fi
cd .Sudoku-Destroyer

