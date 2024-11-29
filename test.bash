#!/bin/bash
# SPDX-FileCopyrightText: 2024 Kensuke Sato
# SPDX-License-Identifier: BSD-3-Clause

res=0
bash install_bash.sh
res=$?
[ "${res}" = 1 ] && echo "install error" && exit ${res}
cat test_input.txt | SDS
res=$?
[ "${res}" = 1 ] && echo "SDS error" && exit ${res}
bash uninstall_bash.sh
res=$?
[ "${res}" = 1 ] && echo "uninstall error"
[ "${res}" = 0 ] && echo "all clear"
exit ${res}
