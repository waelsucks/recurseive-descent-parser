#include "parser.hpp"

namespace cat
{
    auto parser::parse() -> void
    {
        int max_null = 20;
        int null_count = 0;

        while (has_next())
        {
            auto result_node = parse_statement();

            if (result_node != nullptr)
                m_nodes.push_back(result_node);
            else if (null_count++ >= max_null)
                break;
        }
    }

    auto parser::parse_statement() -> node *
    {
        // Check for statements

        auto next = peek();

        if (next.type == token_type::TOKEN_NEWLINE)
        {
            consume();
            return nullptr;
        }

        if (next.type == token_type::TOKEN_VARIABLE)
        {

            // Assignment Expressions

            auto next_next = peek_next(1);

            if ((next_next->type == token_type::TOKEN_OPERATOR) && next_next->value == "=")
            {
                auto result_tree = parse_assignment_expression();
                return result_tree;
            }
        }

        // Call Expression Statement

        if (next.type == token_type::TOKEN_CALL)
            return parse_call_expression();

        auto result_tree = parse_expression();

        return result_tree;
    }

    auto parser::parse_assignment_expression() -> node *
    {
        auto variable_name = peek();
        consume();
        auto equals = peek();
        consume();

        auto args = parse_statement();

        assignment_node *result_node = new assignment_node(variable_name.value, args);
        return result_node;
    }

    auto parser::parse_expression() -> node *
    {
        auto left = parse_term_expression();
        auto next = peek();

        while (next.value != "")
        {
            if (next.type != token_type::TOKEN_OPERATOR)
                break;

            consume();

            auto right = parse_term_expression();

            if (next.value == "+")
                left = new addition_node(left, right);
            if (next.value == "-")
                left = new subtraction_node(left, right);

            next = peek();
        }

        return left;
    }

    auto parser::parse_term_expression() -> node *
    {
        auto left = parse_factor_expression();

        if (left == nullptr)
            return nullptr;

        auto next = peek();

        while (next.value != "")
        {
            if (next.value != "*" && next.value != "/")
                break;

            consume();

            auto right = parse_term_expression();

            if (next.value == "*")
                left = new multiplication_node(left, right);
            if (next.value == "/")
                left = new division_node(left, right);

            next = peek();
        }

        return left;
    }

    auto parser::parse_factor_expression() -> node *
    {
        auto token = peek();

        if (token.value == "")
            return nullptr;

        consume();

        if (token.type == token_type::TOKEN_INTEGER)
        {
            integer_node *result_node = new integer_node(token);
            return result_node;
        }

        if (token.type == token_type::TOKEN_P_L)
        {
            auto a = parse_expression();

            if (a == nullptr)
                return nullptr;

            token = peek();

            if (token.type == token_type::TOKEN_P_R)
            {
                consume();
                return a;
            }

            else
                return nullptr;
        }

        if (token.type == token_type::TOKEN_VARIABLE) {
            // assignment_node *return_node = new assignment_node(token.value, 0);
            variable_node *return_node = new variable_node(token.value);
            return return_node;
        }
        // {

        //     auto right = parse_statement();

        //     assignment_node *return_node = new assignment_node(token.value, 0);
        //     return return_node;

        // }

        return nullptr;
    }

    auto parser::parse_call_expression() -> node *
    {

        auto call_statement_name = peek();
        consume();

        if (call_statement_name.value == "print")
        {
            auto arg = parse_expression();

            call_expression_node *node = new call_expression_node(call_statement_name, arg);
            return node;
        }

        if (call_statement_name.value == "config")
        {
            auto arg = peek();

            if (arg.value != "dec" && arg.value != "hex" && arg.value != "bin")
                throw std::runtime_error("ERROR: Invalid argument");

            consume();

            argument_node *node = new argument_node(arg);
            call_expression_node *return_node = new call_expression_node(call_statement_name, node);

            return return_node;
        }

        return nullptr;
    }

    auto parser::consume() -> token { return m_tokens[m_cursor++]; }
    auto parser::peek() const -> token { return m_tokens[m_cursor]; }
    auto parser::peek_next(int i) const -> std::optional<token>
    {
        if ((m_cursor + i) > m_tokens.size())
            return {};

        return m_tokens[m_cursor + i];
    }
    auto parser::has_next() const -> bool { return m_cursor < m_tokens.size(); }
    auto parser::program() -> std::vector<node *> { return m_nodes; }

} // namespace cat
