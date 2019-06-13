#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <set>
#include <windows.h>
#include <algorithm>
#include <memory>

#include "Digraph.h"

int main() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	int width = 0;
	int height = 0;
	std::string path;

	std::cout << "Width: " << std::endl;
	std::cin >> width;
	std::cout << "Height: " << std::endl;
	std::cin >> height;

	std::cout << "Path: " << std::endl;
	std::cin >> path;

	std::ifstream file(path);
	std::string line;

	std::vector<std::vector<char>> chars(height, std::vector<char>(width));
	std::unique_ptr<Digraph> graph = std::make_unique<Digraph>(height * width);

	int rowCounter = 0;
	int columCounter = 0;

	while (std::getline(file, line))
	{
		for (auto character : line) {
			chars[rowCounter][columCounter] = character;
			++columCounter;
		}
		columCounter = 0;
		++rowCounter;
	}

	for (int i = 0; i < chars.size(); ++i) {
		for (int j = 0; j < chars[i].size(); ++j) {

			if (chars[i][j] == '#')
				continue;

			int v = i * width + j;
			int w = 0;

			// Add bottom
			if (i - 1 >= 0) {
				if (chars[i - 1][j] != '#') {
					w = (i - 1) * width + j;
					graph->addEdge(v, w);
				}
			}

			// Add front
			if (j - 1 >= 0) {
				if (chars[i][j - 1] != '#') {
					w = i * width + (j - 1);
					graph->addEdge(v, w);
				}
			}

			// Add back
			if (j + 1 < width) {
				if (chars[i][j + 1] != '#') {
					w = i * width + (j + 1);
					graph->addEdge(v, w);
				}
			}

			// Add top
			if (i + 1 < height) {
				if (chars[i + 1][j] != '#') {
					w = (i + 1) * width + j;
					graph->addEdge(v, w);
				}
			}

		}
	}

	int startRow = -1;
	int startColumn = -1;

	int destinationRow = -1;
	int destinationColumn = -1;

	std::cout << "Starting row (not zero based): " << std::endl;
	std::cin >> startRow;
	std::cout << "Starting column (not zero based): " << std::endl;
	std::cin >> startColumn;

	std::cout << "Destination row (not zero based): " << std::endl;
	std::cin >> destinationRow;
	std::cout << "Destination column (not zero based): " << std::endl;
	std::cin >> destinationColumn;

	int startPosition = (startRow - 1) * width + (startColumn - 1);
	int destinationPostion = (destinationRow - 1) * width + (destinationColumn - 1);

	graph->bfs(startPosition);
	auto hasPath = graph->hasPathTo(destinationPostion);

	if (hasPath) {
		auto steps = graph->pathTo(destinationPostion);

		system("CLS");

		for (int i = 0; i < chars.size(); ++i) {
			for (int j = 0; j < chars[i].size(); ++j) {
				int v = i * width + j;
				if (steps->find(v) != steps->end()) {
					SetConsoleTextAttribute(hConsole, 12);
					std::cout << "P";
				}
				else {
					SetConsoleTextAttribute(hConsole, 15);
					std::cout << chars[i][j];
				}
			}
			std::cout << std::endl;
		}
	}
	else {
		std::cout << "No path found!" << std::endl;
	}

	std::getchar();
	std::getchar();

	return 0;
}