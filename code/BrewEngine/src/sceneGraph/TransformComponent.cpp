#include "brewEngine/sceneGraph/TransformComponent.h"
#include <glm/gtc/matrix_transform.hpp>

namespace gl3::brewEngine::sceneGraph {
    TransformComponent::TransformComponent(guid_t owner, TransformComponent* parentTransform,
        glm::vec2 position, float zRotation, glm::vec2 scale, float radius)
            : Component(owner),
            localPosition(position),
            localZRotation(zRotation),
            localScale(scale),
            radius(radius),
            modelMatrix(glm::identity<glm::mat4>()) {
        setParent(parentTransform);
    }

    TransformComponent::TransformComponent(TransformComponent &&other) noexcept
            : localPosition(other.localPosition),
            localZRotation(other.localZRotation),
            localScale(other.localScale),
            radius(other.radius),
            modelMatrix(other.modelMatrix),
            children(std::move(other.children)){
        owner = other.owner;
        setParent(other.parent);
    }

    TransformComponent *TransformComponent::getParent() {
        return parent;
    }

    void TransformComponent::setParent(TransformComponent *parentTransform) {
        parent = parentTransform;
        if(parent != nullptr) {
            parent->addChild(this);
        }
    }

    void TransformComponent::addChild(TransformComponent *transform) {
        children.insert(transform);
    }

    void TransformComponent::removeChild(TransformComponent *transform) {
        children.erase(transform);
    }

    std::set<TransformComponent *> TransformComponent::getChildTransforms() {
        return children;
    }

    void TransformComponent::invalidate() {
        deleted = true;
        parent = nullptr;
        for (auto child: children) {
            child->invalidate();
        }
        children.clear();
    }

    TransformComponent::~TransformComponent() {
        if(parent != nullptr) {
            parent->removeChild(this);
        }
        invalidate();
    }

}
