#pragma once

#include "EcpEntity.h"


#include <set>
#include <memory>
#include <unordered_map>

typedef unsigned int ComponentType;
static const ComponentType invalidct = 0;
typedef std::set<ComponentType> componentTypeSet;


struct Component {
	static const ComponentType _type;
};

class IcomponentStore {
public:
	typedef std::unique_ptr<IcomponentStore> ptr;
};

template<typename C>
class ComponentStore : public IcomponentStore {
	static_assert(std::is_base_of<Component, C>::value, "C must derived from the Component struct");
	static_assert(C::_type != invalidct, "C must define a valid non-zero _mType");

public:
	ComponentStore() {

		}
	~ComponentStore() {

	}

	inline bool add(const EcpEntity e, C&& c) {
		return store.insert(std::make_pair(e, std::move(c))).second;
	}
	inline bool remove(EcpEntity e) {
		return(0 < store.erase(e));
	}
	inline bool has(EcpEntity e) const {
		return (store.end() != store.find(e));
	}

	inline C& get(EcpEntity e) {
		return store.at(e);
	}

	inline C extract(EcpEntity e) {
		C component = std::move(store.at(e));
		store.erase(e);
		return component;
	}
	inline const std::unordered_map<EcpEntity, C>& getComponents() {
		return store;
	}

private:
	std::unordered_map<EcpEntity, C> store;
	static const ComponentType _type = C::_type;


};