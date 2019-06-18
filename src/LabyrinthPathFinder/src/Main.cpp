#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <set>
#include <windows.h>
#include <memory>
#include <chrono>

#include "Digraph.h"

auto main() -> int
{
	const auto h_console = GetStdHandle(STD_OUTPUT_HANDLE);

	size_t width = 0;
	size_t height = 0;
	std::string path;

	std::cout << "Width: " << std::endl;
	std::cin >> width;
	std::cout << "Height: " << std::endl;
	std::cin >> height;

	std::cout << "Path: " << std::endl;
	std::cin >> path;

	auto start_one = std::chrono::high_resolution_clock::now();

	std::ifstream file(path);
	std::string line;

	std::vector<std::vector<char>> chars(height, std::vector<char>(width));
	const auto graph = std::make_unique<digraph>(height * width);

	auto row_counter = 0;
	auto column_counter = 0;

	while (std::getline(file, line))
	{
		for (auto character : line) {
			chars[row_counter][column_counter] = character;
			++column_counter;
		}
		column_counter = 0;
		++row_counter;
	}

	for (size_t i = 0; i < chars.size(); ++i) {
		for (size_t j = 0; j < chars[i].size(); ++j) {

			if (chars[i][j] == '#')
				continue;

			const auto v = i * width + j;
			auto w = 0;

			// Add bottom
			if (i - 1 >= 0 && chars[i - 1][j] != '#') {
				w = (i - 1) * width + j;
				graph->add_edge(v, w);
			}

			// Add front
			if (j - 1 >= 0 && chars[i][j - 1] != '#') {
				w = i * width + (j - 1);
				graph->add_edge(v, w);
			}

			// Add back
			if (j + 1 < width && chars[i][j + 1] != '#') {
				w = i * width + (j + 1);
				graph->add_edge(v, w);
			}

			// Add top
			if (i + 1 < height && chars[i + 1][j] != '#') {
				w = (i + 1) * width + j;
				graph->add_edge(v, w);
			}

		}
	}

	size_t start_row = -1;
	size_t start_column = -1;

	size_t destination_row = -1;
	size_t destination_column = -1;

	auto end_one = std::chrono::high_resolution_clock::now();

	std::cout << "Starting row (not zero based): " << std::endl;
	std::cin >> start_row;
	std::cout << "Starting column (not zero based): " << std::endl;
	std::cin >> start_column;

	std::cout << "Destination row (not zero based): " << std::endl;
	std::cin >> destination_row;
	std::cout << "Destination column (not zero based): " << std::endl;
	std::cin >> destination_column;

	auto start_two = std::chrono::high_resolution_clock::now();

	const auto start_position = (start_row - 1) * width + (start_column - 1);
	const auto destination_position = (destination_row - 1) * width + (destination_column - 1);

	graph->bfs(start_position, destination_position);
	const auto has_path = graph->has_path_to(destination_position);

	if (has_path) {
		auto steps = graph->path_to(destination_position);

		auto end_two = std::chrono::high_resolution_clock::now();

		system("CLS");

		auto result = std::chrono::duration<double, std::milli>((end_one - start_one) + (end_two - start_two));

		std::cout << "The past time is " << result.count() << " milliseconds" << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;

		for (size_t i = 0; i < chars.size(); ++i) {
			for (size_t j = 0; j < chars[i].size(); ++j) {
				const auto v = i * width + j;
				if (steps->find(v) != steps->end()) {
					SetConsoleTextAttribute(h_console, 12);
					std::cout << "P";
				}
				else {
					SetConsoleTextAttribute(h_console, 15);
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
