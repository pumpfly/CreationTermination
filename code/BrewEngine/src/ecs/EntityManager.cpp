// EntityManager.cpp
#include "brewEngine/ecs/EntityManager.h"
#include "brewEngine/Game.h"


namespace gl3::brewEngine::ecs {
    EntityManager::EntityManager(ComponentManager &componentManager,Game &game)
            : componentManager(componentManager) {
        game.onAfterUpdate.addListener([&](Game &) {
            purgeEntities();
        });
    }

    Entity &EntityManager::createEntity() {
        auto guid = entityCounter++;
        Entity entity(guid, componentManager);
        entities[guid] = std::make_unique<Entity>(entity);
        return getEntity(guid);
    }

    Entity &EntityManager::getEntity(const guid_t guid) {
        return *entities.at(guid).get();
    }

    void EntityManager::deleteEntity(Entity &entity) {
        entity.deleted = true;
        entity.deleteAllComponents();
        deleteList.push_back(entity.guid());
    }

    void EntityManager::purgeEntities() {
        for(auto &guid: deleteList) {
            entities.erase(guid);
        }
        deleteList.clear();
    }
}