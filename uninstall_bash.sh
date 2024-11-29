#!/bin/sh
# SPDX-FileCopyrightText: 2024 Kensuke Sato
# SPDX-License-Identifier: BSD-3-Clause

cd ~
if grep -q "export PATH+=:~/.Sudoku_Solver/" "./.bashrc"; then
	sed -i -e "s@export PATH+=:~/.Sudoku_Solver/@@g" ~/.bashrc;
fi


