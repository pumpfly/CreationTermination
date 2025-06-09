#include "brewEngine/ecs/ComponentManager.h"
#include "brewEngine/Game.h"

namespace gl3::brewEngine::ecs {
    ComponentManager::ComponentManager(brewEngine::Game &engine) {
        engine.onAfterUpdate.addListener([&](Game &) {
           purgeComponents();
        });
    }

    void ComponentManager::removeComponents(guid_t entityID) {
        for(auto &[componentTypeID, componentContainer]: containers) {
            const auto &component = componentContainer.find(entityID);
            const auto componentExistsInContainer = component != componentContainer.end();
            if(componentExistsInContainer) component->second->deleted = true;
            deleteList.emplace_back(componentTypeID, entityID);
        }
    }

    void ComponentManager::purgeComponents() {
        for(const auto &[componentTypeID, ownerID]: deleteList) {
            containers.at(componentTypeID).erase(ownerID);
        }
        deleteList.clear();
    }

}