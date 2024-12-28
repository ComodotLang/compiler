#include "codegen.h"


void CodegenVisitor::visit(IttBinaryOperationNode& node) {
    node.getLhs().accept(*this);
    llvm::Value* lhs = this->getValue();

    node.getRhs().accept(*this);
    llvm::Value* rhs = this->getValue();

    llvm::Value* result = nullptr;
    switch (node.getOperation()) {
        case IttBinaryOperation::ADD:
            result = _builder->CreateAdd(lhs, rhs, "addtmp");
            break;
        case IttBinaryOperation::SUB:
            result = _builder->CreateSub(lhs, rhs, "subtmp");
            break;
        case IttBinaryOperation::MUL:
            result = _builder->CreateMul(lhs, rhs, "multmp");
            break;
        case IttBinaryOperation::DIV:
            result = _builder->CreateSDiv(lhs, rhs, "divtmp");
            break;
        case IttBinaryOperation::LESS_THEN:
            result = _builder->CreateICmpSLT(lhs, rhs, "lesstmp");
            break;
        case IttBinaryOperation::GREATER_THEN:
            result = _builder->CreateICmpSGT(lhs, rhs, "greatertmp");
            break;
        case IttBinaryOperation::EQUALS:
            result = _builder->CreateICmpEQ(lhs, rhs, "eqtmp");
            break;
        default:
            throw std::runtime_error("Unsupported binary operation");
    }

    this->assignGeneratedValue(result);
}


void CodegenVisitor::visit(IttVariableNode& node) {

}

void CodegenVisitor::visit(IttFunctionNode& node) {
    std::vector<llvm::Type*> paramTypes;
    for (const auto& param : node.getParameters()) {
        paramTypes.push_back(getLLVMType(param.second));
    }
    llvm::FunctionType* funcType = llvm::FunctionType::get(
        getLLVMType(node.getType()), 
        paramTypes,
        false                        
    );

    llvm::Function* function = llvm::Function::Create(
        funcType,
        llvm::Function::ExternalLinkage,
        node.getName(),
        _buildingModule.get()
    );

    llvm::BasicBlock* entry = llvm::BasicBlock::Create(_context, "entry", function);
    _builder->SetInsertPoint(entry);

    node.getBody().accept(*this);

    if (!_builder->GetInsertBlock()->getTerminator()) {
        _builder->CreateRetVoid();
    }
}

void CodegenVisitor::visit(IttBlockNode& node) {
    std::for_each(node.getStatements().begin(), node.getStatements().end(), [this](const std::unique_ptr<IttNode>& blockPart) {
        blockPart->accept(*this);
    });
}

void CodegenVisitor::visit(IttIntegerNode& node) {
    llvm::Type *int32Type = llvm::Type::getInt32Ty(_context);

    this->assignGeneratedValue(
        llvm::ConstantInt::get(int32Type, node.getValue())
    );
}

void CodegenVisitor::visit(IttFloatNode& node) {
    llvm::Type *floatType = llvm::Type::getFloatTy(_context);

    this->assignGeneratedValue(
        llvm::ConstantInt::get(floatType, node.getValue())
    );
}

void CodegenVisitor::visit(IttBooleanNode& node) {
    llvm::Type *floatType = llvm::Type::getInt1Ty(_context);

    this->assignGeneratedValue(
        llvm::ConstantInt::get(floatType, node.getValue())
    );
}

void CodegenVisitor::visit(IttCharNode& node) {
    llvm::Type *floatType = llvm::Type::getInt8Ty(_context);

    this->assignGeneratedValue(
        llvm::ConstantInt::get(floatType, node.getValue())
    );
}

void CodegenVisitor::visit(IttReturnNode& node) {
    if (node.getReturnStmt().has_value()) {
        IttNode* returnContent = node.getReturnStmt()->get();
        returnContent->accept(*this);

        llvm::Value* returnValue = this->getValue();

        _builder->CreateRet(returnValue);
    } else {
        _builder->CreateRetVoid();
    }
}

llvm::Type* CodegenVisitor::getLLVMType(IttType type) {
    switch (type.getKind()) {
        case IttType::INT: return llvm::Type::getInt32Ty(_context);
        case IttType::FLOAT: return llvm::Type::getFloatTy(_context);
        case IttType::BOOL: return llvm::Type::getInt1Ty(_context);
        case IttType::CHAR: return llvm::Type::getInt8Ty(_context);
        default: throw std::runtime_error("Unsupported type");
    }
}