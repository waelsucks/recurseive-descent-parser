#include "interpreter.hpp"

namespace cat
{
    auto interpreter::eval(node *input_node) -> int
    {
        if (input_node->type == NODE_TYPE::CALL_EXPRESSION_NODE)
        {
            call_expression_node *node = dynamic_cast<call_expression_node *>(input_node);

            if (node->m_call_expression.value == "config")
            {
                auto arg = node->m_arg->evaluate();

                if (arg.value != "dec" && arg.value != "hex" && arg.value != "bin")
                    std::runtime_error("ERROR: Invalid syntax. Must be [ hex | dec | bin ]");

                m_mode = arg.value == "dec" ? MODES::DEC : arg.value == "hex" ? MODES::HEX
                                                                              : MODES::BIN;
                return 0;
            }

            if (node->m_call_expression.value == "print")
            {
                auto result = eval_expression(node->m_arg);

                if (m_mode == MODES::HEX)
                    std::cout << "cat: 0x" << std::hex << result << std::endl;
                else if (m_mode == MODES::DEC)
                    std::cout << "cat: " << std::dec << result << std::endl;
                else if (m_mode == MODES::BIN)
                    std::cout << "cat: " << std::bitset<8>(result) << std::endl;

                return 0;
            }
        }

        if (input_node->type == NODE_TYPE::ASSIGNMENT_NODE)
        {
            assignment_node *node = dynamic_cast<assignment_node *>(input_node);
            auto args = eval_expression(node->m_value);

            m_variables[node->m_variable_name] = args;
            return args;
        }
    }

    auto interpreter::eval_expression(node *node_to_evaluate) -> int
    {
        auto arg_type = node_to_evaluate->type;

        if (arg_type == NODE_TYPE::VARIABLE_NODE)
        {
            if (m_variables.find(node_to_evaluate->evaluate().value) == m_variables.end())
            {
                std::string error = "ERROR: " + node_to_evaluate->evaluate().value + " not defined";
                throw std::runtime_error(error);
            }

            auto variable_node_to_evaluate = dynamic_cast<variable_node *>(node_to_evaluate);
            return m_variables[variable_node_to_evaluate->m_variable_name];
        }

        if (arg_type == NODE_TYPE::ADDITION_NODE ||
            arg_type == NODE_TYPE::SUBTRACTION_NODE ||
            arg_type == NODE_TYPE::MULTIPLICATION_NODE ||
            arg_type == NODE_TYPE::DIVITION_NODE)
        {
            auto addition_node_to_evaluate = static_cast<addition_node *>(node_to_evaluate); // Should make a general operator node...

            auto left_value = eval_expression(addition_node_to_evaluate->left);
            auto right_value = eval_expression(addition_node_to_evaluate->right);

            switch (arg_type)
            {
            case NODE_TYPE::ADDITION_NODE:
                return left_value + right_value;
                break;

            case NODE_TYPE::SUBTRACTION_NODE:
                return left_value - right_value;
                break;

            case NODE_TYPE::MULTIPLICATION_NODE:
                return left_value * right_value;
                break;

            case NODE_TYPE::DIVITION_NODE:
                return left_value / right_value;
                break;

            default:
                break;
            }
        }

        if (node_to_evaluate->type == NODE_TYPE::ASSIGNMENT_NODE)
        {
            // Chaining assignment nodes
            return eval(node_to_evaluate);
        }

        if (node_to_evaluate->type == NODE_TYPE::INTEGER_NODE)
            return std::stoi(node_to_evaluate->evaluate().value);

        return 0;
    }

}