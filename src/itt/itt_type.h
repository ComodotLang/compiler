#pragma once
#include <string>

class IttType {
  public:
    enum TypeKind {
        INT,
        CHAR,
        BOOL,
        VOID,
        FLOAT,
        IDENTIFIER,
        UNRESOLVED,
    };

  private:
    TypeKind _kind;

  public:
    explicit IttType(TypeKind kind) : _kind(kind) {}

    TypeKind getKind() const { return _kind; }

    std::string toString() const {
        switch (_kind) {
        case INT: return "Int";
        case CHAR: return "Char";
        case BOOL: return "Bool";
        case VOID: return "Void";
        case FLOAT: return "Float";
        case UNRESOLVED: return "Unresolved";
        default: return "Unknown";
        }
    }

    bool operator==(const IttType& other) const {
      return _kind == other._kind;
    }
};