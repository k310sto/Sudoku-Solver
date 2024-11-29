#!/bin/sh
# SPDX-FileCopyrightText: 2024 Kensuke Sato
# SPDX-License-Identifier: BSD-3-Clause

gcc solver.c -o SDS
cd ~
if find -name "Sudoku_Solver" | grep -q "./Sudoku_Solver"; then
	mv ~/Sudoku_Solver ~/.Sudoku_Solver
else
    if ! find -name ".Sudoku_Solver" | grep -q "./.Sudoku_Solver"; then
        echo "Sudoku_Solverがホームディレクトリにありません"
    fi
fi
if ! grep -q "export PATH+=:~/.Sudoku_Solver/" "./.bashrc"; then
	echo "export PATH+=:~/.Sudoku_Solver/" >> ~/.bashrc;
fi
bash

