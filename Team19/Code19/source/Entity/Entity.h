#pragma once
#include <string>

class Entity {
protected:
    int stmtNo;
    std::string name;
    std::string type;

public:
    Entity() = default;
    Entity(int stmtNo, std::string name, std::string type);
    int getStmtNo() const;
    std::string getName() const;
    bool operator==(const Entity& other) const;
    bool operator!=(const Entity& other) const;
    std::string getType();

};

namespace std {
    template<> struct hash<Entity> {
        size_t operator()(Entity const& entity) const {
            size_t stmtNoHash = std::hash<int>()(entity.getStmtNo());
            size_t nameHash = std::hash<std::string>()(entity.getName()) << 1;
            return stmtNoHash ^ nameHash;
        }
    };
}

namespace Ent {
    struct Constant : Entity {
        Constant(int stmtNo, std::string name) : Entity(stmtNo, name, "constant") {}
    };

    struct Variable : Entity {
        Variable(int stmtNo, std::string name) : Entity(stmtNo, name, "variable") {}
    };

    struct Statement : Entity {
        Statement(int stmtNo, std::string name) : Entity(stmtNo, name, "statement") {}
    };

    struct Procedure : Entity {
        Procedure(int stmtNo, std::string name) : Entity(0, name, "procedure") {};
        Procedure(std::string name) : Entity(0, name, "procedure") {}
    };
}