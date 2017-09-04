#pragma once
#include "EcpManager.h";

/*


struct position : public Component {
float x;
float y;
position(float xx, float yy) : x(xx), y(yy) {

}
};

const ComponentType position::_type = 1;

class SystemMove : public EcpSystem {
public:
SystemMove(EcpManager& manager) : EcpSystem(manager) {
componentTypeSet requiredComponents;
requiredComponents.insert(position::_type);
setRequiredComponents(std::move(requiredComponents));

}

virtual void updateEntity(EcpEntity e) {
position& pos = manager.getComponentStore<position>().get(e);

pos.x++;
}

};

class SystemMove2 : public EcpSystem {
public:
SystemMove2(EcpManager& manager) : EcpSystem(manager) {
componentTypeSet requiredComponents;
requiredComponents.insert(position::_type);
setRequiredComponents(std::move(requiredComponents));

}

virtual void updateEntity(EcpEntity e) {
position& pos = manager.getComponentStore<position>().get(e);

pos.x -= 2;
}

};
class SystemPrint : public EcpSystem {
public:
SystemPrint(EcpManager& manager) :
EcpSystem(manager) {
componentTypeSet requiredComponents;
requiredComponents.insert(position::_type);
setRequiredComponents(std::move(requiredComponents));
}
virtual void updateEntity(EcpEntity e) {
position& pos = manager.getComponentStore<position>().get(e);

std::cout << "ENTITY X: " << pos.x << std::endl;
}
};
EcpEntity theentity;

	manager.createComponentStore<position>();

	manager.addSystem(EcpSystem::ptr(new SystemMove(manager)));

	manager.addSystem(EcpSystem::ptr(new SystemPrint(manager)));

    theentity = manager.createEntity();
	
	manager.addComponent(theentity, position(2.0f, 2.0f));
	manager.registerEntity(theentity);
	manager.addSystem(EcpSystem::ptr(new SystemMove2(manager)));
	manager.registerEntity(theentity);*/



EcpManager::EcpManager() :
	lastEntity(invalid),
	entities(),
	componentStores(),
	systems(){

}
EcpManager::~EcpManager() {

}

void EcpManager::addSystem(const EcpSystem::ptr & systemptr)
{
	systems.push_back(systemptr);
}

size_t EcpManager::registerEntity(const EcpEntity e)
{
	size_t associatedSystems = 0;

	auto en = entities.find(e);
	if (entities.end() == en) {
		throw std::runtime_error("ENTITY ISIN VOID");
	}
	auto ec = (*en).second;
	for (auto s = systems.begin(); s != systems.end(); ++s) {
		auto src = (*s)->getRequiredComponents();
		if (std::includes(ec.begin(), ec.end(), src.begin(), src.end())) {
			(*s)->registerEntity(e);
			++associatedSystems;
		}
	}


	return associatedSystems;
}

size_t EcpManager::unregisterEntity(const EcpEntity e)
{
	size_t nbAssociatedSystems = 0;

	auto entity = entities.find(e);
	
	auto entityComponents = (*entity).second;

	for (auto s = systems.begin();
		s != systems.end();
		++s) {
		nbAssociatedSystems += (*s)->unregisterEntity(e);
	}

	return nbAssociatedSystems;
}

size_t EcpManager::updateEntities()
{
	size_t nbUpdatedEntities = 0;

	for (auto system = systems.begin();
		system != systems.end();
		++system) {
		nbUpdatedEntities += (*system)->updateEntities();
	}

	return nbUpdatedEntities;
}

