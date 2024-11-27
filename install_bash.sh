#!/bin/sh

gcc ./destroyer.c -o ./destroyer
gcc ./destroyer-f.c -o ./destroyer-f
cd ~
if find -name "Sudoku-Destroyer" | grep -q "Sudoku-Destroyer"; then
	mv ~/Sudoku-Destroyer ~/.Sudoku-Destroyer
else echo "名前変更済"
fi
if ! grep -q "export PATH+=:~/.Sudoku-Destroyer/" "./.bashrc"; then
	echo "export PATH+=:~/.Sudoku-Destroyer/" >> ~/.bashrc;
else echo "PATH設定済"
fi
bash

