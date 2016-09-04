#include "Npc.h"
#include "Math.h"


Npc::Npc(TextureCache texCache)
{
	_tex = texCache.getTexture("Npc.png");
	_angle = 0;
	_x = 1024;
	_y = 1024;
	_xTile = 512;
}


Npc::~Npc()
{
}


void Npc::update(Tile tiles[1024])
{

	
	int currentTile = _x / 64 + (_y / 64) * 32;
	
	if (currentTile != _xTile) {
		
		findPath(tiles);
	}


}

void Npc::draw(SpriteBatch &spriteBatch) {
	spriteBatch.draw(glm::vec4(_x,_y,32,32),glm::vec4(0.0f,0.0f,1.0f,1.0f),_tex,1.0f,ColorRGBA8(255,255,255,255),_angle);
	for (std::vector<int>::iterator it = path.begin(); it != path.end(); it++) {
		int dx = (*it % 32)*64;
		int dy = floor(*it / 32)*64;
		
		spriteBatch.draw(glm::vec4(dx, dy, 32, 32), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), _tex, 1.0f, ColorRGBA8(255, 255, 255, 255), _angle);
	}
}

void Npc::setTargetTile(int x)
{
	_xTile = x;
	
}


void Npc::findPath(Tile tiles[1024]) {
	std::vector<Node> fullList;

	fullList.reserve(1000);

	std::vector<Node> openList;
	std::vector<Node> closedList;

	int currentTile = _x / 64 + (_y / 64) * 32;
	
	// set the starting node as the current tile the npc is on
	openList.push_back(Node(NULL,currentTile,0,0,0 ));

	// add a node that will always be the furthest away node possible
	Node tmpn(NULL, 0, 9999, 0, 0);

	//the node we are checking. set it to tmpn so that it will be overwritten immediately
	Node* Q = &tmpn;

	while(Q->_x != _xTile){
		std::vector<Node>::iterator it;
		std::vector<Node>::iterator lowestIt;

		Q = &tmpn;

		//check which node in the open list has the smallest F value, aka is fastest to move to.
		for (it = openList.begin(); it != openList.end();it++) {
			if (it->_f < Q->_f) {
				// if a faster node than q is found, use that node
				Q = &(*it);

				//get the lowest node to be removed from the openlist immediately
				lowestIt = it;
			}
		}
		//add the node to the fullist, because from now on it can be a parent node and thus it must be preserved
		fullList.push_back(*Q);

		//now chance the place to where Q is pointing to the space in memory the fullist allocated it to
		Q = &fullList.back();

		//remove the lowest node now that we have found it.
		openList.erase(lowestIt);

		//give the lowest node it' s children, aka the surrounding nodes which are most quickly reached by going through the current parent node
		std::vector<Node> children;

		//generate the children by going through the surrounding coordinates.
		int qTileLoc = Q->_x;
		for (int i =  -1; i < 2; i++) {
			for (int k = -32; k < 33; k+=32) {
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
			if (it->_x == _xTile) {

				//if we've got a path, remove the previous path
				path.clear();

				//add the new path or something
				path.push_back(it->_x);

				//error checking if tile has no parent aka is the end of the line
				if (it->_parent == NULL) {
					std::cout << "QWE";
					return;
				}
				Node* np = Q;
				 //filling out the rest of the path
				while (np->_parent->_x != currentTile) {
					path.push_back(np->_x);
					std::cout << path.size() << std::endl;
					if (np->_parent == NULL) {
						std::cout << "ASDADS";
						return;
					}
					np = np->_parent;
				
				}
			
				return;
			}
			else {
				it->_g = Q->_g + 10;
				// calculate the heuristic value of the child
				it->_h = calculateH(it->_x);
				
				it->_f = it->_g + it->_h;

				bool skipChild = false;

				// if the child is already in the openlist, and has a greater _f value, don' t add it again
				for (std::vector<Node>::iterator openListIt = openList.begin(); openListIt != openList.end(); openListIt++) {
					if (openListIt->_x == it->_x &&  openListIt->_f < it->_f) {
						skipChild = true;
					}
				}

				//fuck it, what is in the closed list stays in the closed list. No matter the F value.
				for (std::vector<Node>::iterator closedListIt = closedList.begin(); closedListIt != closedList.end(); closedListIt++) {
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



}

int Npc::calculateH(int x) {
	int xDistance = abs(x % 32 - _xTile % 32);
	int yDistance = abs((x - x % 32) / 32 - (_xTile - _xTile % 32) / 32);
	return xDistance + yDistance;
}