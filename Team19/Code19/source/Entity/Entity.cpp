#pragma once

#include "Entity.h"
#include <typeinfo>

Entity::Entity(int stmtNo, std::string name, std::string type) {
    this->stmtNo = stmtNo;
    this->name = name;
    this->type = type;
}

int Entity::getStmtNo() const {
    return stmtNo;
}

std::string Entity::getName() const {
    return name;
}

std::string Entity::getType() {
    return type;
}

bool Entity::operator==(const Entity& other) const {
    if (this == &other) {
        return true;
    }
    else if (typeid(this) != typeid(other)) {
        return false;
    }
    return this->getStmtNo() == other.stmtNo && this->getName() == other.name;
}