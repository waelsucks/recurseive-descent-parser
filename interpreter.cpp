#include "interpreter.hpp"

namespace cat
{
    auto interpreter::eval(node *input_node) -> void
    {
        if (input_node->type == NODE_TYPE::CALL_EXPRESSION_NODE)
        {
            call_expression_node *node = dynamic_cast<call_expression_node *>(input_node);

            if (node->m_call_expression.value == "config")
            {
                // Check if we need to change the configuration mode

                auto arg = node->m_arg->evaluate();

                if (arg.value != "dec" && arg.value != "hex" && arg.value != "bin")
                    std::runtime_error("ERROR: Invalid syntax. Must be [ hex | dec | bin ]");

                m_mode = arg.value == "dec" ? MODES::DEC : arg.value == "hex" ? MODES::HEX
                                                                              : MODES::BIN;
                return;
            }

            if (node->m_call_expression.value == "print")
            {
                // Print statements. Evaluate right side of expression

                auto result = eval_expression(node->m_arg);

                if (m_mode == MODES::HEX)
                    std::cout << "cat: 0x" << std::hex << result << std::endl;
                else if (m_mode == MODES::DEC)
                    std::cout << "cat: " << std::dec << result << std::endl;
                else if (m_mode == MODES::BIN)
                    std::cout << "cat: " << std::bitset<8>(result) << std::endl;
            }
        }

        if (input_node->type == NODE_TYPE::ASSIGNMENT_NODE)
        {
            assignment_node *node = dynamic_cast<assignment_node *>(input_node);
            auto args = eval_expression(node->m_value);

            m_variables[node->m_variable_name] = args;
        }
    }

    auto interpreter::eval_expression(node *node_to_evaluate) -> int
    {
        auto arg_type = node_to_evaluate->type;

        if (arg_type == NODE_TYPE::VARIABLE_NODE)
        {

            // If variable is not defined, throw an error

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
            auto addition_node_to_evaluate = static_cast<addition_node *>(node_to_evaluate);

            auto left = addition_node_to_evaluate->left;
            auto right = addition_node_to_evaluate->right;

            auto left_value = eval_expression(left);
            auto right_value = eval_expression(right);

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

        return std::stoi(node_to_evaluate->evaluate().value);
    }

}
