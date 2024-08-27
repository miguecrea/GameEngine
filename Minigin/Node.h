#pragma once

struct Node
{
	int y;
	int x;
	int parentX;
	int parentY;
	float gCost;//distance from starting node
	float hCost;//distance from ending  <- choosing factor 2
	float fCost;//g cost + h cost <- choosing factor 1
};
