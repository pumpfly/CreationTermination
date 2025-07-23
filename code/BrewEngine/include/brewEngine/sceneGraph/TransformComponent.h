#pragma once
#include <set>
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"
#include "brewEngine/ecs/ecs.h"
#include "brewEngine/ecs/Component.h"

//This forward declaration is not part of the sommer semester blockkurs, but without it, I get an "is not declared" error
namespace gl3::brewEngine::ecs {
    class ComponentManager;
    class Entity;
}

using gl3::brewEngine::ecs::Component;
using gl3::brewEngine::ecs::ComponentManager;
using gl3::brewEngine::ecs::Entity;
using gl3::brewEngine::ecs::guid_t;

namespace gl3::brewEngine::sceneGraph {
    /// The @class TransformComponent stores position, rotation, scale and also radius of the entities.
    class TransformComponent final : public Component {
        friend ComponentManager;
        friend Entity;

    public:
        std::set<TransformComponent *> getChildTransforms();
        TransformComponent *getParent();
        void setParent(TransformComponent *parentTransform);
        void invalidate();

        ~TransformComponent() override;
        TransformComponent(const TransformComponent&) = delete;
        TransformComponent& operator = (const TransformComponent&) = delete;
        TransformComponent& operator = (TransformComponent&&) = delete;
        TransformComponent(TransformComponent &&other) noexcept;

        glm::vec2 localPosition;
        float localZRotation;
        glm::vec2 localScale;
        float radius;
        glm::mat4 modelMatrix;


    protected:
        void addChild(TransformComponent *transform);
        void removeChild(TransformComponent *transform);

    private:
        explicit TransformComponent(guid_t owner,
                           TransformComponent *parentTransform = nullptr,
                           glm::vec2 position = {0, 0},
                           float zRotation = 0,
                           glm::vec2 scale = {1, 1},
                           float radius = 1.0f);

        TransformComponent *parent = nullptr;
        std::set<TransformComponent *> children;
    };
}