#pragma once

#include <string>
#include <vector>
#include <memory.h>
#include <optional>
#include <memory>

enum BinaryOperator {
    SUB = 0,
    DIV,
    ADD,
    MUL
};

class IVisitor {
public:
    virtual void visit(class IntegerNode& node) = 0;
    virtual void visit(class FloatNode& node) = 0;
    virtual void visit(class IdentifierNode& node) = 0;
    virtual void visit(class BinaryOperationNode& node) = 0;
    virtual void visit(class VarDefNode& node) = 0;
    virtual void visit(class ReturnNode& node) = 0;
    virtual void visit(class BlockNode& node) = 0;
    virtual void visit(class FunctionNode& node) = 0;
    virtual void visit(class CallNode& node) = 0;
};

class INode {
public:
    virtual void accept(IVisitor& visitor) = 0;
    virtual ~INode() {};
};

class IntegerNode : public INode {
    int _value;
public:
    IntegerNode(int val): _value(val) {}

    int getValue() const { return _value; }

    void accept(IVisitor& visitor) override {
        visitor.visit(*this);
    }
};

class FloatNode : public INode {
    float _value;
public:
    FloatNode(float val) : _value(val) {}

    float getValue() const { return _value; }

    void accept(IVisitor& visitor) override {
        visitor.visit(*this);
    }
};

class IdentifierNode : public INode {
    std::string _name;
public:
    IdentifierNode(std::string name): _name(name) {}

    std::string getName() const { return _name; }

    void accept(IVisitor& visitor) override {
        visitor.visit(*this);
    }
};

class BinaryOperationNode : public INode {
    std::shared_ptr<INode> _lhs;
    std::shared_ptr<INode> _rhs;
    BinaryOperator _op;
public:
    BinaryOperationNode(std::shared_ptr<INode> lhs, std::shared_ptr<INode> rhs, BinaryOperator op): _lhs(lhs), _rhs(rhs), _op(op) {}

    INode& getLhs() const { return *_lhs.get(); }
    INode& getRhs() const { return *_rhs.get(); }

    BinaryOperator getOp() const { return _op; }

    void accept(IVisitor& visitor) override {
        visitor.visit(*this);
    }
};

class VarDefNode : public INode {
    std::string _name;
    std::shared_ptr<INode> _content;
public:
    VarDefNode(std::string name, std::shared_ptr<INode> content): _name(name), _content(content) {}

    INode& getContent() const { return *_content.get(); }

    const std::string& getName() const { return _name; }

    void accept(IVisitor& visitor) override {
        visitor.visit(*this);
    }
};

class ReturnNode : public INode {
    std::optional<std::shared_ptr<INode>> _retData;

public:
    explicit ReturnNode(std::optional<std::shared_ptr<INode>> data)
        : _retData(data) {}

    void accept(IVisitor& visitor) override {
        visitor.visit(*this);
    }

    std::optional<INode*> getRetData() const {
        if (_retData && _retData.value()) {
            return _retData.value().get();
        }
        return std::nullopt;
    }
};

class BlockNode : public INode {
    std::vector<std::shared_ptr<INode>> _nodes;
public:
    BlockNode(std::vector<std::shared_ptr<INode>>& nodes): _nodes(nodes) {}

    void accept(IVisitor& visitor) override {
        visitor.visit(*this);
    }

    const std::vector<std::shared_ptr<INode>>& getNodes() const {
        return _nodes;
    }
};

class FunctionNode : public INode {
    std::string _name;
    std::string _retType; //replace with tokens
    std::string _visibility; //replace with tokens
    std::vector<std::tuple<std::string, std::string>> _args; //replace with tokens
    std::shared_ptr<BlockNode> _body;
public:
    FunctionNode(
        std::string name, 
        std::string retType, 
        std::string visibility, 
        std::vector<std::tuple<std::string, 
        std::string>> args, 
        std::shared_ptr<BlockNode> body)
        : _name(name), _retType(retType), _visibility(visibility), _args(args), _body(body) {}
    
    void accept(IVisitor& visitor) override {
        visitor.visit(*this);
    }

    const std::string& getName() const { return _name; }

    const std::string& getReturnType() const { return _retType; }

    const std::string& getVisibility() const { return _visibility; }

    const std::vector<std::tuple<std::string, std::string>>& getArgs() const { return _args; }

    BlockNode& getBody() const { return *_body.get(); }
};

class CallNode : INode {
    std::optional<std::string> _alias;
    std::string _name;
    std::vector<std::shared_ptr<INode>> _args;
public: 
    CallNode(
        std::optional<std::string> alias, 
        std::string name, 
        std::vector<std::shared_ptr<INode>> args) 
        : _alias(alias), _name(name), _args(args) {}

    void accept(IVisitor& visitor) override {
        visitor.visit(*this);
    }

    const std::optional<std::string>& getAlias() const { return _alias; }

    const std::string& getName() const { return _name; }

    const std::vector<std::shared_ptr<INode>>& getArgs() const { return _args; }
};
