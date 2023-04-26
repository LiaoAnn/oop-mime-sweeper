# Minesweeper

A Classic Minesweeper

## Using

to run at GUI mode

```
./Minesweeper.exe GUI
```

![2023-04-23](2023-04-23.png)

![2023-04-23-1](2023-04-23-1.png)

```
Language: C++
main contributor: 劉耀恩
```
### Installation Guide
```
  QT version 6.5 
  Visual studio 2022
```
### Operation Guide 
```
  1.Set the file location.
  2.clone in the main branch. (gh repo clone LiaoAnn/oop-mime-sweeper)
  3.If gh is not support, you need to install the github CLI.
  4.run the commend "git checkout -f New-framework".(branch name: New-framework) 
  5.run the commend "ls -al" to see the branch content.
  6.If you clone it successfully, then open the project name ( 0414.sln ) by Visual studio 2022. (because of the version problem, only Visual studio 2022 can debug it)
  7.install the QT visual studio tool in menu Manage extensions.
  8.In QT vs tool, find the options, and set the path to find the file qmake.exe(C:\Qt\6.5.0\msvc2019_64\bin\qmake) 
  9.Build and run the program and it display the QtwidgetApplication.
  10.In QtWidgetApplication, you can choose the column, row, mines to set the game's Degree of difficulty.
  11. Also, you can choose the file mode and load the file, which is in the file board(oop-mime-sweeper\boards) and choose the file to load it
  12. When you are playing the minesweeper, right click means flag, and then if you click right click again, it displays "?". Then if you click right click again, it become normal    illusion(white blank).
  13.In the upper left corner, you can print the gameboard, bombcount, and so on.
  14 if you click the bomb, then the QtWidgetApplication will show each bomb location. Game over.
  15.if you find all the bomb, and then you complete the game.
```

### File List
```
main.cpp
MineSweeperElement.cpp
CommandLine.cpp
CommandMap.cpp
CommandMode.cpp
GameWindow.cpp
generateMinesweeperBoard.cpp
RunMode.cpp
StartWindow.cpp
```

### copyright
```
Copyright (c) 2023 National Taiwan University of Science and Technology . All rights reserved.
```

### Licesne
```
SPDX-License-Identifier: Apache-2.0
```