#include <iostream>
#include <memory>
#include <functional>

// Node representing an expression
class ExpressionNode {
public:
    virtual double evaluate() const = 0;
    virtual ~ExpressionNode() {}
};

// Node for a numeric value
class ValueNode : public ExpressionNode {
public:
    ValueNode(double value) : value_(value) {}
    double evaluate() const override { return value_; }

private:
    double value_;
};

// Node for a binary operation
class BinaryOpNode : public ExpressionNode {
public:
    BinaryOpNode(char op, std::unique_ptr<ExpressionNode> left, std::unique_ptr<ExpressionNode> right)
        : op_(op), left_(std::move(left)), right_(std::move(right)) {}

    double evaluate() const override {
        switch (op_) {
            case '+':
                return left_->evaluate() + right_->evaluate();
            case '-':
                return left_->evaluate() - right_->evaluate();
            case '*':
                return left_->evaluate() * right_->evaluate();
            case '/':
                return left_->evaluate() / right_->evaluate();
            default:
                throw std::runtime_error("Invalid operator");
        }
    }

private:
    char op_;
    std::unique_ptr<ExpressionNode> left_;
    std::unique_ptr<ExpressionNode> right_;
};

int main() {
    // Build an expression tree: 3 + (4 * 2)
    std::unique_ptr<ExpressionNode> expressionTree =
        std::make_unique<BinaryOpNode>(
            '+',
            std::make_unique<ValueNode>(3.0),
            std::make_unique<BinaryOpNode>(
                '*',
                std::make_unique<ValueNode>(4.0),
                std::make_unique<ValueNode>(2.0)
            )
        );

    // Evaluate the expression
    double result = expressionTree->evaluate();
    
    // Print the result
    std::cout << "Result: " << result << std::endl;

    return 0;
}