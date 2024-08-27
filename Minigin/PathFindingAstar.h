#pragma once

#include"iostream"
#include"vector"
#include <queue>
#include <cmath>
#include<set>
#include <stack>
#include"Map.h"
#include"Node.h"

#define X_MAX 224
#define X_STEP 8
#define Y_MAX 288
#define Y_STEP 8


std::vector<Node> makePath(std::vector<std::vector<Node>> map, Node dest);
bool isValid(int x, int y);

inline bool operator < (const Node& lhs, const Node& rhs)
{//We need to overload "<" to put our struct into a set
	return lhs.fCost < rhs.fCost;
}

bool isDestination(int x, int y, Node dest) {
	if (x == dest.x && y == dest.y) {
		return true;
	}
	return false;
}

//raycast para saltar 

double calculateH(int x, int y, Node dest) {
	double H = (sqrt((x - dest.x) * (x - dest.x)
		+ (y - dest.y) * (y - dest.y)));
	return H;
}

std::vector<Node> aStar(Node agent, Node dest) {
	std::vector<Node> empty;
	if (!isValid(dest.x, dest.y)) {
		//std::cout << "Destination is an obstacle" << std::endl;
		return empty;
	}
	if (isDestination(agent.x, agent.y, dest)) {
		//std::cout << "You are the destination" << std::endl;
		return empty;
	}

	// Dynamically allocate memory for the closedList
	bool** closedList = new bool* [X_MAX / X_STEP];
	for (int i = 0; i < X_MAX / X_STEP; ++i) {
		closedList[i] = new bool[Y_MAX / Y_STEP];
		std::fill_n(closedList[i], Y_MAX / Y_STEP, false);
	}

	// Dynamically allocate memory for the allMap
	std::vector<std::vector<Node>> allMap(X_MAX / X_STEP,
		std::vector<Node>(Y_MAX / Y_STEP));

	// Initialize whole map
	for (int x = 0; x < X_MAX / X_STEP; x++) {
		for (int y = 0; y < Y_MAX / Y_STEP; y++) {
			allMap[x][y].fCost = FLT_MAX;
			allMap[x][y].gCost = FLT_MAX;
			allMap[x][y].hCost = FLT_MAX;
			allMap[x][y].parentX = -1;
			allMap[x][y].parentY = -1;
			allMap[x][y].x = x;
			allMap[x][y].y = y;

			closedList[x][y] = false;
		}
	}

	// Initialize starting point
	int x = agent.x;
	int y = agent.y;
	allMap[x][y].fCost = 0.0;
	allMap[x][y].gCost = 0.0;
	allMap[x][y].hCost = 0.0;
	allMap[x][y].parentX = x;
	allMap[x][y].parentY = y;

	std::vector<Node> openList;
	openList.emplace_back(allMap[x][y]);
	bool destinationFound = false;

	while (!openList.empty() && openList.size() < (X_MAX / X_STEP) * (Y_MAX / Y_STEP)) {
		Node node;
		//it = next(it)
		do {
			float temp = FLT_MAX;
			std::vector<Node>::iterator itNode;
			for (std::vector<Node>::iterator it = openList.begin();
				it != openList.end(); ++it) {
				Node n = *it;
				if (n.fCost < temp)
				{
					temp = n.fCost;
					itNode = it;
				}
			}
			node = *itNode;
			openList.erase(itNode);
		} while (!isValid(node.x, node.y) && !openList.empty());

		x = node.x;
		y = node.y;
		closedList[x][y] = true;

		for (int newX = -1; newX <= 1; newX++)
		{
			for (int newY = -1; newY <= 1; newY++) {
				double gNew, hNew, fNew;
				if (isValid(x + newX, y + newY)) {
					if (isDestination(x + newX, y + newY, dest)) {
						allMap[x + newX][y + newY].parentX = x;
						allMap[x + newX][y + newY].parentY = y;
						destinationFound = true;

						// Clean up dynamically allocated memory
						for (int i = 0; i < X_MAX / X_STEP; ++i) {
							delete[] closedList[i];
						}
						delete[] closedList;

						return makePath(allMap, dest);
					}
					else if (!closedList[x + newX][y + newY]) {
						gNew = node.gCost + 1.0;
						hNew = calculateH(x + newX, y + newY, dest);
						fNew = gNew + hNew;
						if (allMap[x + newX][y + newY].fCost == FLT_MAX ||
							allMap[x + newX][y + newY].fCost > fNew)
						{
							if (newX != 0 && newY != 0) {
								fNew = FLT_MAX;
								gNew = FLT_MAX;
								hNew = FLT_MAX;
							}
							allMap[x + newX][y + newY].fCost = float(fNew);
							allMap[x + newX][y + newY].gCost = float(gNew);
							allMap[x + newX][y + newY].hCost = float(hNew);
							allMap[x + newX][y + newY].parentX = x;
							allMap[x + newX][y + newY].parentY = y;
							openList.emplace_back(allMap[x + newX][y + newY]);
						}
					}
				}
			}
		}
	}
	if (!destinationFound) {
		//std::cout << "Destination not found" << std::endl;
		for (int i = 0; i < X_MAX / X_STEP; ++i) {
			delete[] closedList[i];
		}
		delete[] closedList;
		return empty;
	}
	return empty;
}

std::vector<std::vector<Node>> getPaths(Node agent, Node dest, int pathNumber) {
	
	std::vector<std::vector<Node>> paths;
	paths.reserve(pathNumber);
	if (!isValid(dest.x, dest.y)) {
		//std::cout << "Destination is an obstacle" << std::endl;
		return paths;
	}
	if (isDestination(agent.x, agent.y, dest)) {
		//std::cout << "You are the destination" << std::endl;
		return paths;
	}

	// Dynamically allocate memory for the closedList
	bool** closedList = new bool* [X_MAX / X_STEP];
	for (int i = 0; i < X_MAX / X_STEP; ++i) {
		closedList[i] = new bool[Y_MAX / Y_STEP];
		std::fill_n(closedList[i], Y_MAX / Y_STEP, false);
	}

	// Dynamically allocate memory for the allMap
	std::vector<std::vector<Node>> allMap(X_MAX / X_STEP,
		std::vector<Node>(Y_MAX / Y_STEP));

	// Initialize whole map
	for (int x = 0; x < X_MAX / X_STEP; x++) {
		for (int y = 0; y < Y_MAX / Y_STEP; y++) {
			allMap[x][y].fCost = FLT_MAX;
			allMap[x][y].gCost = FLT_MAX;
			allMap[x][y].hCost = FLT_MAX;
			allMap[x][y].parentX = -1;
			allMap[x][y].parentY = -1;
			allMap[x][y].x = x;
			allMap[x][y].y = y;

			closedList[x][y] = false;
		}
	}

	// Initialize starting point
	int x = agent.x;
	int y = agent.y;
	allMap[x][y].fCost = 0.0;
	allMap[x][y].gCost = 0.0;
	allMap[x][y].hCost = 0.0;
	allMap[x][y].parentX = x;
	allMap[x][y].parentY = y;

	std::vector<Node> openList;
	openList.emplace_back(allMap[x][y]);
	bool destinationFound = false;

	while ((!openList.empty() && openList.size() < (X_MAX / X_STEP) * (Y_MAX / Y_STEP)) || paths.size() < pathNumber) {
		Node node;
		//it = next(it)
		do {
			float temp = FLT_MAX;
			std::vector<Node>::iterator itNode;
			for (std::vector<Node>::iterator it = openList.begin();
				it != openList.end(); ++it) {
				Node n = *it;
				if (n.fCost < temp)
				{
					temp = n.fCost;
					itNode = it;
				}
			}
			node = *itNode;
			openList.erase(itNode);
		} while (!isValid(node.x, node.y) && !openList.empty());

		x = node.x;
		y = node.y;
		closedList[x][y] = true;

		for (int newX = -1; newX <= 1; newX++)
		{
			for (int newY = -1; newY <= 1; newY++) {
				double gNew, hNew, fNew;
				if (isValid(x + newX, y + newY)) {
					if (isDestination(x + newX, y + newY, dest)) {
						allMap[x + newX][y + newY].parentX = x;
						allMap[x + newX][y + newY].parentY = y;
						destinationFound = true;

						// Clean up dynamically allocated memory
						for (int i = 0; i < X_MAX / X_STEP; ++i) {
							delete[] closedList[i];
						}
						delete[] closedList;

						paths.push_back(makePath(allMap, dest));
					}
					else if (!closedList[x + newX][y + newY]) {
						gNew = node.gCost + 1.0;
						hNew = calculateH(x + newX, y + newY, dest);
						fNew = gNew + hNew;
						if (allMap[x + newX][y + newY].fCost == FLT_MAX ||
							allMap[x + newX][y + newY].fCost > fNew)
						{
							if (newX != 0 && newY != 0) {
								fNew = FLT_MAX;
								gNew = FLT_MAX;
								hNew = FLT_MAX;
							}
							allMap[x + newX][y + newY].fCost = float(fNew);
							allMap[x + newX][y + newY].gCost = float(gNew);
							allMap[x + newX][y + newY].hCost = float(hNew);
							allMap[x + newX][y + newY].parentX = x;
							allMap[x + newX][y + newY].parentY = y;
							openList.emplace_back(allMap[x + newX][y + newY]);
						}
					}
				}
			}
		}
	}
	if (!destinationFound) {
		//std::cout << "Destination not found" << std::endl;
		for (int i = 0; i < X_MAX / X_STEP; ++i) {
			delete[] closedList[i];
		}
		delete[] closedList;
		return paths;
	}
	return paths;
}

bool isValid(int x, int y)
{
	//If our Node is an obstacle it is not valid
	// int id = x + y * (X_MAX / X_STEP);

	if (x < 0 || y < 0 || x >= (X_MAX / X_STEP) || y >= (Y_MAX / Y_STEP))
	{
		return false;
	}
	if (dae::Map::GetInstance().MapArray[y][x] == 1)
	{
		return false;
	}
	return true;
}

std::vector<Node> makePath(std::vector<std::vector<Node>> map, Node dest) {
	try {
		//std::cout << "Found a path" << std::endl;
		int x = dest.x;
		int y = dest.y;
		std::stack<Node> path;
		std::vector<Node> usablePath;

		while (!(map[x][y].parentX == x && map[x][y].parentY == y)
			&& map[x][y].x != -1 && map[x][y].y != -1)
		{
			path.push(map[x][y]);
			int tempX = map[x][y].parentX;
			int tempY = map[x][y].parentY;
			x = tempX;
			y = tempY;

		}
		path.push(map[x][y]);

		while (!path.empty()) {
			Node top = path.top();
			path.pop();
			usablePath.emplace_back(top);
		}
		//std::cout << "Path full, " << usablePath.size() << std::endl;
		return usablePath;
	}
	catch (const std::exception& e) {
		std::cout << "Path empty, error " << e.what() << std::endl;
		return std::vector<Node>();
	}
}
