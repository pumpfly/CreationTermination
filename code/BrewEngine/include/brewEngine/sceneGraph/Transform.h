#pragma once
#include <set>
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"
#include "brewEngine/ecs/ecs.h"
#include "brewEngine/ecs/Component.h"

//This forward declaration is not part of the sommer semester blockkurs, but without it i get a "is not declared" error
namespace gl3::brewEngine::ecs {
    class ComponentManager;
    class Entity;
}

using gl3::brewEngine::ecs::Component;
using gl3::brewEngine::ecs::ComponentManager;
using gl3::brewEngine::ecs::Entity;
using gl3::brewEngine::ecs::guid_t;

namespace gl3::brewEngine::sceneGraph {
    class Transform final : public Component {
        friend ComponentManager;
        friend Entity;

    public:
        std::set<Transform *> getChildTransforms();
        Transform *getParent();
        void setParent(Transform *parentTransform);
        void invalidate();

        ~Transform() override;
        Transform(const Transform&) = delete;
        Transform& operator = (const Transform&) = delete;
        Transform& operator = (Transform&&) = delete;
        Transform(Transform &&other) noexcept;

        glm::vec3 localPosition;
        float localZRotation;
        glm::vec3 localScale;
        glm::mat4 modelMatrix;


    protected:
        void addChild(Transform *transform);
        void removeChild(Transform *transform);

    private:
        explicit Transform(guid_t owner,
                           Transform *parentTransform = nullptr,
                           glm::vec3 position = {0, 0, 0},
                           float zRotation = 0,
                           glm::vec3 scale = {1, 1, 1});

        Transform *parent = nullptr;
        std::set<Transform *> children;
    };
}