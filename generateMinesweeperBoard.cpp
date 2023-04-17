#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

void generateMinesweeperBoard(char board[10][10], int width, int height, int minesCount) {
	// Randomly generate mines
	std::srand(std::time(nullptr));
	for (int i = 0; i < minesCount; ++i) {
		int x = std::rand() % width;
		int y = std::rand() % height;
		if (board[x][y] != '*') {
			board[x][y] = '*';
		}
		else {
			--i;
		}
	}

	// Fill in the numbers
	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < height; ++j) {
			if (board[i][j] == '*') {
				continue;
			}
			char count = '0';
			if (i > 0 && j > 0 && board[i - 1][j - 1] == '*') {
				++count;
			}
			if (i > 0 && board[i - 1][j] == '*') {
				++count;
			}
			if (i > 0 && j < height - 1 && board[i - 1][j + 1] == '*') {
				++count;
			}
			if (j > 0 && board[i][j - 1] == '*') {
				++count;
			}
			if (j < height - 1 && board[i][j + 1] == '*') {
				++count;
			}
			if (i < width - 1 && j > 0 && board[i + 1][j - 1] == '*') {
				++count;
			}
			if (i < width - 1 && board[i + 1][j] == '*') {
				++count;
			}
			if (i < width - 1 && j < height - 1 && board[i + 1][j + 1] == '*') {
				++count;
			}
			board[i][j] = count;
		}
	}
}