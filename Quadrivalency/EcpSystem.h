#pragma once
#include <memory>
#include <set>
#include "EcpComponent.h"
#include "EcpEntity.h"

class EcpManager;

class EcpSystem {
public:



	typedef std::shared_ptr<EcpSystem> ptr;
	explicit EcpSystem(EcpManager& manager);
	~EcpSystem();

	inline const componentTypeSet& getRequiredComponents() const {
		return requiredComponents;
	}

	inline bool registerEntity(EcpEntity e) {
		return matchingEntities.insert(e).second;
	}
	inline size_t unregisterEntity(EcpEntity e) {
		return matchingEntities.erase(e);
	}
	inline bool hasEntity(EcpEntity e) const {
		return (matchingEntities.end() != matchingEntities.find(e));
	}

	size_t updateEntities();

	virtual void updateEntity(EcpEntity e) = 0;

protected:
	inline void setRequiredComponents(componentTypeSet&& rc) {
		requiredComponents = std::move(rc);
	}

	EcpManager& manager;

private:

	componentTypeSet requiredComponents;
	std::set<EcpEntity> matchingEntities;

};