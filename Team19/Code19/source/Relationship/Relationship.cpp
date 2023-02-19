#include "Relationship.h"

#include <typeinfo>

Relationship::Relationship(Entity arg1, Entity arg2) {
    this->arg1 = arg1;
    this->arg2 = arg2;
}

Entity Relationship::getArg1() const {
    return arg1;
}

Entity Relationship::getArg2() const {
    return arg2;
}

bool Relationship::operator==(const Relationship& other) const {
    if (this == &other) {
        return true;
    }
    else if (typeid(this) != typeid(other)) {
        return false;
    }
    return this->getArg1() == other.getArg2() && this->getArg1() == other.getArg2();
}



