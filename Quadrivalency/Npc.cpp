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


	std::vector<Node> openList;
	std::vector<Node> closedList;

	int currentTile = _x / 64 + (_y / 64) * 32;
	
	
	openList.push_back(Node(NULL,currentTile,0,0,0 ));

	while(openList.size() > 0){
		Node tmpn(nullptr, 0, 9999, 0, 0);
		Node* Q = &tmpn;
		std::vector<Node>::iterator it;
		std::vector<Node>::iterator lowestIt;
		for (it = openList.begin(); it != openList.end();it++) {
			if (it->_f < Q->_f) {
				Q = &(*it);
				lowestIt = it;
			}
		}
		openList.erase(lowestIt);

		std::vector<Node> children;

		int qTileLoc = Q->_x;
		for (int i =  -1; i < 2; i++) {
			for (int k = -32; k < 33; k+=32) {
				if (qTileLoc + i + k != qTileLoc) {
					if (tiles[qTileLoc + i + k]._exist) {
						children.push_back(Node(Q, qTileLoc + i + k, 0, 0, 0));
					}
				}
			}
		}
	
		for (it = children.begin(); it != children.end(); it++) {
			if (it->_x == _xTile) {

				path.clear();

				path.push_back(it->_x);

				if (it->_parent == NULL) {
					std::cout << "QWE";
					return;
				}
				Node* np = it->_parent;

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
				it->_h = 100;
				it->_f = it->_g + it->_h;

				bool skipChild = false;

				for (std::vector<Node>::iterator openListIt = openList.begin(); openListIt != openList.end(); openListIt++) {
					if (openListIt->_x == it->_x &&  openListIt->_f < it->_f) {
						skipChild = true;
					}
				}
				for (std::vector<Node>::iterator closedListIt = closedList.begin(); closedListIt != closedList.end(); closedListIt++) {
					if (closedListIt->_x == it->_x &&  closedListIt->_f < it->_f) {
						skipChild = true;
					}
				}
				if (skipChild)
					continue;

				openList.push_back(*it);


			}
			closedList.push_back(*Q);
		}



	}



}