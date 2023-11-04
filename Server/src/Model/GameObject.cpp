//
// Created by abraham on 30/10/23.
//

#include "GameObject.h"

GameObject::GameObject(const Entity& aEntity) : typeEntity(aEntity), body(nullptr) {
}


b2Body *GameObject::getBody() {
    return body;
}

void GameObject::destroyBody() {
    isDestroyed = true;
}

bool GameObject::isDestroyedBody() {
    return this->isDestroyed;
}

Entity GameObject::getEntityType() const {
    return typeEntity;
}
