#pragma once
#include "tile.h"
#include "Node.h"
#include <list>

class PathFinder
{
public:
	static std::vector<int> findPath(Tile tiles[1024], int currentLocation, int destination);

private:
	static int calculateH(int x, int destination);
};