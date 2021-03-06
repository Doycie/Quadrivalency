#include "PathFinder.h"

std::vector<int> PathFinder::findPath(Tile tiles[1024], int currentLocation, int destination) {
	std::vector<int> path;

	//stores all tile that have been checked, so that we only need pointers from other tiles to this list.
	std::list<Node> tileList;

	std::list<Node> openList;
	std::list<Node> closedList;

	// set the starting node as the current tile the npc is on
	openList.push_back(Node(NULL, currentLocation, 0, 0, 0));

	// add a node that will always be the furthest away node possible
	Node tmpn(NULL, 0, 9999, 0, 0);

	//the node we are checking.
	Node* Q = &tmpn;

	// first check if we've reached the desired location already
	while (Q->_x != destination && !openList.empty()) {
		std::list<Node>::iterator it;
		std::list<Node>::iterator lowestIt;

		Q = &tmpn;

		//check which node in the open list has the smallest F value, aka is fastest to move to.
		for (it = openList.begin(); it != openList.end(); it++) {
			if (it->_f < Q->_f) {
				// if a faster node than q is found, use that node
				Q = &(*it);

				//get the lowest node to be removed from the openlist immediately
				lowestIt = it;
			}
		}

		//add the node to the fullist, because from now on it can be a parent node and thus it must be preserved
		tileList.push_back(*Q);

		//now chance the place to where Q is pointing to the space in memory the fullist allocated it to
		Q = &tileList.back();

		//remove the lowest node now that we have found it.
		openList.erase(lowestIt);

		//give the lowest node it' s children, aka the surrounding nodes which are most quickly reached by going through the current parent node
		std::list<Node> children;

		//generate the children by going through the surrounding coordinates.
		int qTileLoc = Q->_x;
		for (int i = -1; i < 2; i++) {
			for (int k = -32; k < 33; k += 32) {
				//prevent the node from becoming it' s own child
				if (qTileLoc + i + k != qTileLoc) {
					//make sure we only use nodes that are passable
					if (tiles[qTileLoc + i + k]._exist) {
						children.push_back(Node(Q, qTileLoc + i + k, 0, 0, 0));
					}
				}
			}
		}

		//go through all of it' s children
		for (it = children.begin(); it != children.end(); it++) {
			if (it->_x == destination) {
				//if we've got a path, remove the previous path
				path.clear();

				//add the new path or something
				path.push_back(it->_x);

				Node* np = Q;
				//filling out the rest of the path
				while (np->_x != currentLocation) {
					path.push_back(np->_x);
					std::cout << path.size() << std::endl;
					if (np->_parent == NULL) {
						std::cout << "ASDADS";
						return path;
					}
					np = np->_parent;
				}

				return path;
			}
			else {
				it->_g = Q->_g + 10;
				// calculate the heuristic value of the child
				it->_h = calculateH(it->_x, destination);

				it->_f = it->_g + it->_h;

				bool skipChild = false;

				// if the child is already in the openlist, and has a greater _f value, don' t add it again
				for (std::list<Node>::iterator openListIt = openList.begin(); openListIt != openList.end(); openListIt++) {
					if (openListIt->_x == it->_x &&  openListIt->_f < it->_f) {
						skipChild = true;
					}
				}

				//fuck it, what is in the closed list stays in the closed list. No matter the F value.
				for (std::list<Node>::iterator closedListIt = closedList.begin(); closedListIt != closedList.end(); closedListIt++) {
					if (closedListIt->_x == it->_x) {
						skipChild = true;
					}
				}
				if (skipChild)
					continue;

				openList.push_back(*it);
			}
		}

		closedList.push_back(*Q);
	}

	return path;
}

int PathFinder::calculateH(int x, int destination) {
	int xDistance = abs(x % 32 - destination % 32);
	int yDistance = abs((x - x % 32) / 32 - (destination - destination % 32) / 32);
	return xDistance + yDistance;
}