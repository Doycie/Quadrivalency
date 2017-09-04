#include "EcpSystem.h";

EcpSystem::EcpSystem(EcpManager& m) :
	manager(m) {
}

EcpSystem::~EcpSystem() {
}

/**
* @brief Update function - for all matching Entities.
*
* @param[in] aElapsedTime  Elapsed time since last update call, in seconds.
*/
size_t EcpSystem::updateEntities( ) {
	size_t nbUpdatedEntities = 0;

	for (auto entity = matchingEntities.begin();
		entity != matchingEntities.end();
		++entity) {
		// For each matching Entity, call the specialized System update method.
		updateEntity(*entity);
		++nbUpdatedEntities;
	}

	return nbUpdatedEntities;
}