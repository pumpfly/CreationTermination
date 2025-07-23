#pragma once

#include "ecs.h"

namespace gl3::brewEngine::ecs {
    class Component {
        /// A component is owned by an entity,
        /// they can be seen as a container that stores all the data which belongs to the respective entity.
        /// Therefore, a component of an entity does not store any functions of said entity.
        /// A class becomes a component, by inheriting this class.
        /// Every component class needs to implement @class ComponentManager and @class Entity as a friend class,
        /// for ComponentManager and Entity to access private or protected members/methods.
        friend class ComponentManager;
        friend class Entity;

    public:
        virtual ~Component() = default;

        /// @function entity() returns the guid_t ID of its owner entity.
        [[nodiscard]] guid_t entity() const {return owner;}
        [[nodiscard]] guid_t isDeleted() const {return deleted;}

    protected:
        explicit Component(guid_t owner = invalidID): owner(owner) {};

        guid_t owner;
        bool deleted = false;
    };
}