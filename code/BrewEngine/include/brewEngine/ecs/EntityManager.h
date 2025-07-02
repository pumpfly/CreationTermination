#pragma once

#include <vector>
#include "brewEngine/ecs/ecs.h"
#include "brewEngine/ecs/Entity.h"
#include "brewEngine/ecs/ComponentManager.h"

namespace gl3::brewEngine {
    class Game;
}

namespace gl3::brewEngine::ecs {
    class EntityManager {
    public:
        EntityManager(ComponentManager &componentManager, Game &game);

        Entity& createEntity();
        [[nodiscard]] Entity& getEntity(guid_t guid);
        void deleteEntity(Entity &entity);

    private:
        void purgeEntities();

        ComponentManager &componentManager;
        std::map<guid_t, std::unique_ptr<Entity>> entities;
        std::vector<guid_t> deleteList;
        int entityCounter = 0;
    };
}