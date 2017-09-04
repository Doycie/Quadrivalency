#pragma once
#include "EcpEntity.h";
#include "EcpComponent.h";
#include "EcpSystem.h";
#include <unordered_map>;
#include <map>;
#include <vector>
#include <algorithm>

class EcpManager {
public:
	EcpManager();
	~EcpManager();

	template<typename C>
	inline bool createComponentStore() {
		static_assert(std::is_base_of<Component, C>::value, "C must derived from the Component struct");
		static_assert(C::_type != invalidct, "C must define a valid non-zero _mType");
		return componentStores.insert(std::make_pair(C::_type, IcomponentStore::ptr(new ComponentStore<C>()))).second;
	}

    template<typename C>
	inline ComponentStore<C>& getComponentStore() {
		auto iComponentStore = componentStores.find(C::_type);
		if (componentStores.end() == iComponentStore) {
			throw std::runtime_error("ASD");
		}
		return reinterpret_cast<ComponentStore<C>&>(*(iComponentStore->second));
	}
	void addSystem(const EcpSystem::ptr& systemptr);

	inline EcpEntity createEntity() {
		entities.insert(std::make_pair((lastEntity + 1), componentTypeSet()));
		return (++lastEntity);
	}

	template<typename C>
	inline bool addComponent(const EcpEntity e, C&& c) {
		auto en = entities.find(e);
		if (entities.end() == en) {
			throw std::runtime_error("DSA");
		}

		(*en).second.insert(C::_type);
		return getComponentStore<C>().add(e, std::move(c));
	}

	size_t registerEntity(const EcpEntity e);

	size_t unregisterEntity(const EcpEntity e);

	size_t updateEntities();


private:
	EcpEntity lastEntity;
	std::unordered_map<EcpEntity, componentTypeSet> entities;
	std::map<ComponentType, IcomponentStore::ptr> componentStores;

	std::vector<EcpSystem::ptr> systems;
};