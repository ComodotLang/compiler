#include <memory>
#include <gtest/gtest.h>

#include "ast_to_itt_translator.h"

TEST(TranslatorTests, TestIdentifierTranslation) {
    IdentifierNode identifier("var1");
    AstToIttTranslator translator;
    auto result = translator.translate(identifier);
    ASSERT_NE(result, nullptr);
    auto* identifierNode = dynamic_cast<IttIdentifierNode*>(result.get());
    ASSERT_NE(identifierNode, nullptr);
    EXPECT_EQ(identifierNode->getName(), "var1");
    EXPECT_EQ(identifierNode->getType().getKind(), IttType::UNRESOLVED);
}

TEST(TranslatorTests, TestIntegerTranslation) {
    IntegerNode i(5);
    AstToIttTranslator translator;
    auto result = translator.translate(i);
    ASSERT_NE(result, nullptr);
    auto* intNode = dynamic_cast<IttIntegerNode*>(result.get());
    ASSERT_NE(intNode, nullptr);
    EXPECT_EQ(intNode->getValue(), 5);
}

TEST(TranslatorTests, TestFloatTranslation) {
    FloatNode i(3.23);
    AstToIttTranslator translator;
    auto result = translator.translate(i);
    ASSERT_NE(result, nullptr);
    auto* intNode = dynamic_cast<IttFloatNode*>(result.get());
    ASSERT_NE(intNode, nullptr);
    EXPECT_FLOAT_EQ(intNode->getValue(), 3.23);
}


TEST(TranslatorTests, TestBinaryOpTranslation) {
    auto lhs = std::make_shared<BinaryOperationNode>(
        std::make_shared<IntegerNode>(2), 
        std::make_shared<IntegerNode>(3), 
        ADD
    );
    auto rhs = std::make_shared<IntegerNode>(1);
    BinaryOperationNode bop(lhs, rhs, SUB);  
    AstToIttTranslator translator;

    auto result = translator.translate(bop);
    ASSERT_NE(result, nullptr);

    auto* bopNode = dynamic_cast<IttBinaryOperationNode*>(result.get());
    ASSERT_NE(bopNode, nullptr);

    auto* ittLhs = dynamic_cast<IttBinaryOperationNode*>(&bopNode->getLhs());
    ASSERT_NE(ittLhs, nullptr);
    EXPECT_EQ(ittLhs->getOperation(), IttBinaryOperation::ADD);

    auto* ittLhsLhs = dynamic_cast<IttIntegerNode*>(&ittLhs->getLhs());
    ASSERT_NE(ittLhsLhs, nullptr);
    EXPECT_EQ(ittLhsLhs->getValue(), 2);

    auto* ittLhsRhs = dynamic_cast<IttIntegerNode*>(&ittLhs->getRhs());
    ASSERT_NE(ittLhsRhs, nullptr);
    EXPECT_EQ(ittLhsRhs->getValue(), 3);

    auto* ittRhs = dynamic_cast<IttIntegerNode*>(&bopNode->getRhs());
    ASSERT_NE(ittRhs, nullptr);
    EXPECT_EQ(ittRhs->getValue(), 1);
}

TEST(TranslatorTests, TestVarDefTranslation) {
    auto binOp = std::make_shared<BinaryOperationNode>(
        std::make_shared<IntegerNode>(2), 
        std::make_shared<IntegerNode>(3), 
        ADD
    );
    VarDefNode varDef("var1", binOp);
    AstToIttTranslator translator;
    
    auto result = translator.translate(varDef);
    ASSERT_NE(result, nullptr);

    auto* varNode = dynamic_cast<IttVariableNode*>(result.get());
    ASSERT_NE(varNode, nullptr);

    auto* content = dynamic_cast<IttBinaryOperationNode*>(&varNode->getContent());
    ASSERT_NE(content, nullptr);
    EXPECT_EQ(content->getOperation(), IttBinaryOperation::ADD);

    auto* contentLhs = dynamic_cast<IttIntegerNode*>(&content->getLhs());
    ASSERT_NE(contentLhs, nullptr);
    EXPECT_EQ(contentLhs->getValue(), 2);

    auto* contentRhs = dynamic_cast<IttIntegerNode*>(&content->getRhs());
    ASSERT_NE(contentRhs, nullptr);
    EXPECT_EQ(contentRhs->getValue(), 3);
}

TEST(TranslatorTests, TestBlockTranslation) {
    auto binOp = std::make_shared<BinaryOperationNode>(
        std::make_shared<IntegerNode>(2), 
        std::make_shared<IntegerNode>(3), 
        ADD
    );

    std::vector<std::shared_ptr<INode>> nodes;
    nodes.push_back(binOp);

    BlockNode block(nodes);
    AstToIttTranslator translator;

    auto result = translator.translate(block);
    ASSERT_NE(result, nullptr);

    auto* blockNode = dynamic_cast<IttBlockNode*>(result.get());
    ASSERT_NE(blockNode, nullptr);

    std::vector<std::shared_ptr<IttNode>> sttmts = blockNode->getStatements();
    ASSERT_EQ(sttmts.size(), 1);

    auto sttmt = sttmts[0];

    auto* content = dynamic_cast<IttBinaryOperationNode*>(&*sttmt);
    ASSERT_NE(content, nullptr);
    EXPECT_EQ(content->getOperation(), IttBinaryOperation::ADD);

    auto* contentLhs = dynamic_cast<IttIntegerNode*>(&content->getLhs());
    ASSERT_NE(contentLhs, nullptr);
    EXPECT_EQ(contentLhs->getValue(), 2);

    auto* contentRhs = dynamic_cast<IttIntegerNode*>(&content->getRhs());
    ASSERT_NE(contentRhs, nullptr);
    EXPECT_EQ(contentRhs->getValue(), 3);
}
