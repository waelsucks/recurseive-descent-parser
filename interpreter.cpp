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

                if (node->m_arg->type == NODE_TYPE::VARIABLE_NODE) 
                {
                    // If argument of print statement is a variable, print the value of the variable

                    assignment_node *right_variable = dynamic_cast<assignment_node *>(node->m_arg);

                    auto value = m_variables[right_variable->m_variable_name];

                    if (m_mode == MODES::HEX)
                        std::cout << "cat: 0x" << std::hex << value << std::endl;
                    else if (m_mode == MODES::DEC)
                        std::cout << "cat: " << std::dec << value << std::endl;
                    else if (m_mode == MODES::BIN)
                        std::cout << "cat: " << std::bitset<8>(value) << std::endl;

                    // std::cout << "cat: " << m_variables[right_variable->m_variable_name] << std::endl;
                    return;
                }

                auto value = node->m_arg->evaluate();

                if (m_mode == MODES::HEX)
                    std::cout << "cat: 0x" << std::hex << value.value << std::endl;
                else if (m_mode == MODES::DEC)
                    std::cout << "cat: " << std::dec << value.value << std::endl;
                else if (m_mode == MODES::BIN)
                    std::cout << "cat: " << std::bitset<8>(std::stoi(value.value)) << std::endl;
            }
        }

        if (input_node->type == NODE_TYPE::VARIABLE_NODE)
        {
            assignment_node *node = dynamic_cast<assignment_node *>(input_node);

            if (node->m_value->type == NODE_TYPE::VARIABLE_NODE)
            {

                assignment_node *right_variable = dynamic_cast<assignment_node *>(node->m_value);
                m_variables[node->m_variable_name] = m_variables[right_variable->m_variable_name];

                return;
            }

            

            auto value = node->evaluate();
            m_variables[node->m_variable_name] = std::stoi(value.value);
        }
    }

}
