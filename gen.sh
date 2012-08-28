#!/bin/sh
# Script to generate release files for linux and windows

echo "\033[32mBuilding Linux release...\033[0m"
make clean >/dev/null 2>&1
qmake
make -j 4
if [ ! -f SkeinGUI ]; then
    echo "\033[31mLinux build failed\033[0m"
    return
fi
mv SkeinGUI binaries/linux/
echo "\033[33mLinux build succcessfull :-)\033[0m"

echo
echo "\033[32mBuilding Windows release...\033[0m"
make clean >/dev/null 2>&1
qmake -spec win32-x-g++
make -j 4
if [ -f release/SkeinGUI1.exe ]; then
    echo "\033[31mWindows build failed\033[0m"
    return
fi
mv release/SkeinGUI.exe binaries/win32/
echo "\033[33mWindows build succcessfull :-)\033[0m"

