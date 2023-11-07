#if !defined(NODE_H_)
#define NODE_H_

#include <iostream>
#include "token.hpp"

namespace cat
{
    enum NODE_TYPE
    {
        ADDITION_NODE,
        SUBTRACTION_NODE,
        MULTIPLICATION_NODE,
        DIVITION_NODE,
        NEGATION_NODE,
        VARIABLE_NODE,
        INTEGER_NODE,
        CALL_EXPRESSION_NODE,
        ARGUMENT_NODE,
        BINARY_EXPRESSION_NODE,
        ASSIGNMENT_NODE
    };

    class node
    {
    public:
        node(NODE_TYPE type) : type(type){};
        virtual ~node(){};

        virtual std::string print() = 0;
        virtual token evaluate() = 0;

        NODE_TYPE type;
    };

    class argument_node : public node
    {
    public:
        argument_node(token value) : node(NODE_TYPE::ARGUMENT_NODE), value(value){};
        ~argument_node(){};

        auto print() -> std::string override
        {
            return value.value;
        }

        auto evaluate() -> token override
        {
            return token(token_type::TOKEN_ARGUMENT, value.value);
        }

    public:
        token value;
    };

    class integer_node : public node
    {
    public:
        integer_node(token value) : node(NODE_TYPE::INTEGER_NODE), m_value(value){};
        ~integer_node(){};

        auto print() -> std::string override
        {
            return m_value.value;
        }

        auto evaluate() -> token override
        {
            return m_value;
        }

    public:
        token m_value;
    };

    class call_expression_node : public node
    {
    public:
        call_expression_node(token call_expression, node *arg) : node(NODE_TYPE::CALL_EXPRESSION_NODE), m_call_expression(call_expression), m_arg(arg){};
        ~call_expression_node()
        {
            delete m_arg;
        };

        auto print() -> std::string override
        {
            return "Action: " + m_call_expression.value + ", Args: " + m_arg->print();
        }

        auto evaluate() -> token override
        {
            return m_arg->evaluate();
        }

    public:
        token m_call_expression;
        node *m_arg;
    };

    class binary_expression_node : node
    {
        node *left;
        node *right;
        std::string op;

        binary_expression_node(node *left, node *right, const std::string &op) : node(NODE_TYPE::BINARY_EXPRESSION_NODE), left(left), right(right), op(op){};

        virtual ~binary_expression_node()
        {
            delete left;
            delete right;
        }
    };

    class variable_node : public node
    {
    public:
        variable_node(std::string variable_name) : node(NODE_TYPE::VARIABLE_NODE), m_variable_name(variable_name){};
        ~variable_node(){};

        auto print() -> std::string override
        {
            return m_variable_name;
        }

        auto evaluate() -> token override
        {
            return token(token_type::TOKEN_VARIABLE, m_variable_name);
        }

    public:
        std::string m_variable_name;
    };

    class assignment_node : public node
    {
    public:
        assignment_node(std::string variable_name, node *value) : node(NODE_TYPE::ASSIGNMENT_NODE), m_variable_name(variable_name), m_value(value){};
        ~assignment_node() { delete m_value; }

    public:
        auto print() -> std::string override
        {
            return "[ " + m_variable_name + " ] = " + m_value->print();
        }

        auto evaluate() -> token override
        {
            return m_value->evaluate();
        }

    public:
        std::string m_variable_name;
        node *m_value;
    };

    class addition_node : public node
    {
    public:
        addition_node(node *left, node *right) : node(NODE_TYPE::ADDITION_NODE), left(left), right(right){};
        ~addition_node()
        {
            delete left;
            delete right;
        };

        node *left;
        node *right;

        auto print() -> std::string override
        {
            return "( " + left->print() + " + " + right->print() + " )";
        }

        auto evaluate() -> token override
        {
            int left_result = std::stoi(left->evaluate().value);
            int right_result = std::stoi(right->evaluate().value);

            return token(token_type::TOKEN_INTEGER, std::to_string(left_result + right_result));
        }
    };

    class subtraction_node : public node
    {
    public:
        subtraction_node(node *left, node *right) : node(NODE_TYPE::SUBTRACTION_NODE), left(left), right(right){};
        ~subtraction_node()
        {
            delete left;
            delete right;
        };

        node *left;
        node *right;

        auto print() -> std::string override
        {
            return "( " + left->print() + " - " + right->print() + " )";
        }

        auto evaluate() -> token override
        {
            int left_result = std::stoi(left->evaluate().value);
            int right_result = std::stoi(right->evaluate().value);

            return token(token_type::TOKEN_INTEGER, std::to_string(left_result - right_result));
        }
    };

    class multiplication_node : public node
    {
    public:
        multiplication_node(node *left, node *right) : node(NODE_TYPE::MULTIPLICATION_NODE), left(left), right(right){};
        ~multiplication_node()
        {
            delete left;
            delete right;
        };

        node *left;
        node *right;

        auto print() -> std::string override
        {
            return "( " + left->print() + " * " + right->print() + " )";
        }

        auto evaluate() -> token override
        {
            int left_result = std::stoi(left->evaluate().value);
            int right_result = std::stoi(right->evaluate().value);

            return token(token_type::TOKEN_INTEGER, std::to_string(left_result * right_result));
        }
    };

    class division_node : public node
    {
    public:
        division_node(node *left, node *right) : node(NODE_TYPE::DIVITION_NODE), left(left), right(right){};
        ~division_node()
        {
            delete left;
            delete right;
        };

        node *left;
        node *right;

        auto print() -> std::string override
        {
            return "( " + left->print() + " / " + right->print() + " )";
        }

        auto evaluate() -> token override
        {
            int left_result = std::stoi(left->evaluate().value);
            int right_result = std::stoi(right->evaluate().value);

            return token(token_type::TOKEN_INTEGER, std::to_string(left_result / right_result));
        }
    };

} // namespace cat

#endif // NODE_H_
