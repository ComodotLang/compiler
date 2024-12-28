#pragma once
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/IR/Constant.h>
#include <llvm/IR/Type.h>

#include "../itt/Itt.h"

struct ModuleCodegenCtx {

};

struct GlobalCodegenCtx {

};

class CodegenVisitor: public IttVisitor {
    ModuleCodegenCtx _genContex;
    llvm::LLVMContext _context;
    std::unique_ptr<llvm::Module> _buildingModule;
    std::unique_ptr<llvm::IRBuilder<>> _builder;

    llvm::Value* _generatedValue;

    llvm::Value* getValue() { return _generatedValue; }

    void assignGeneratedValue(llvm::Value* value) { _generatedValue = value; }

    llvm::Type* getLLVMType(IttType type);

public:

    CodegenVisitor(ModuleCodegenCtx& genContext): _genContex(genContext) {
        llvm::InitializeNativeTarget();
        llvm::InitializeNativeTargetAsmParser();
        llvm::InitializeNativeTargetAsmPrinter();
        _builder = std::make_unique<llvm::IRBuilder<>>(_context);
        _buildingModule = std::make_unique<llvm::Module>("test_name", _context);
    }

    const std::unique_ptr<llvm::Module>& getBuildedModule() const { return _buildingModule; }

    void visit(IttBinaryOperationNode& node) override;
    void visit(IttVariableNode& node) override;
    void visit(IttFunctionNode& node) override;
    void visit(IttBlockNode& node) override;
    void visit(IttIntegerNode& node) override;
    void visit(IttFloatNode& node) override;
    void visit(IttBooleanNode& node) override;
    void visit(IttCharNode& node) override;
    void visit(IttReturnNode& node) override;
};