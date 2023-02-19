#pragma once
#include "../../source/Entity/Entity.h"
#include <string>

class Relationship {
protected:
    Entity arg1;
    Entity arg2;

public:
    Relationship() = default;
    Relationship(Entity arg1, Entity arg2);
    Entity getArg1() const;
    Entity getArg2() const;
    bool operator==(const Relationship& other) const;

    struct Relationship::RelationshipHash {
        size_t operator()(const Relationship& relationship) const {
            size_t arg1StmtNoHash = std::hash<int>()(relationship.getArg1().getStmtNo());
            size_t arg1NameHash = std::hash<std::string>()(relationship.getArg1().getName()) << 1;
            size_t arg2StmtNoHash = std::hash<int>()(relationship.getArg2().getStmtNo());
            size_t arg2NameHash = (std::hash<std::string>()(relationship.getArg2().getName()) << 1) >> 1;
            return arg1StmtNoHash ^ arg1NameHash ^ arg2StmtNoHash ^ arg2NameHash;
            return 0;
        }
    };
};

struct Follows : Relationship{
    Follows(Entity arg1, Entity arg2) : Relationship(arg1, arg2) {}
};

struct Modifies : Relationship {
    Modifies(Entity arg1, Entity arg2) : Relationship(arg1, arg2) {}
};

struct Uses : Relationship {
    Uses(Entity arg1, Entity arg2) : Relationship(arg1, arg2) {}
};

struct Parent: Relationship {
    Parent(Entity arg1, Entity arg2) : Relationship(arg1, arg2) {}
};

