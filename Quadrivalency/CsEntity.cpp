#include "CsEntity.h"

CsEntity::CsEntity()
{
}

CsEntity::~CsEntity()
{
}

void CsEntity::init() {
}

void CsEntity::addComponent(CsComponent* c) {
	_components.push_back(c);
}

void CsEntity::removeComponent(std::string ID) {

	for (std::list<CsComponent*>::iterator it = _components.begin(); it != _components.end(); ) {
		if ((*it)->getID() == ID) {
			delete (*it);
			
			_components.erase(it++);
		}
		else ++it;
	}

}
void CsEntity::printComponents() {
	std::cout << "Components: ";
	for (std::list<CsComponent*>::iterator it = _components.begin(); it != _components.end(); it++) {
		std::cout << (*it)->getID() << ", ";
	}
	std::cout << std::endl;
}
CsComponent* CsEntity::getComponent(std::string ID) {
	for (std::list<CsComponent*>::iterator it = _components.begin(); it != _components.end(); ) {
		if ((*it)->getID() == ID) {
			return (*it);
		}
	}
}