#include "lexer.hpp"

namespace cat
{

    auto lexer::tokenize() -> std::vector<token>
    {
        std::vector<token> tokens;

        while (has_next())
            tokens.push_back(next());

        return tokens;
    }

    auto lexer::next() -> token
    {

        if (!has_next())
            return token(token_type::TOKEN_EOF, "");

        consume_space();

        std::string value;

        // Integer
        if (is_integer())
        {
            while (has_next() && is_integer())
                value += peak_consume();

            return token(token_type::TOKEN_INTEGER, value);
        }

        // Whitespace
        if (is_whitespace())
            consume_space();

        // Operator
        if (is_operator())
        {
            value += peak_consume();
            auto next = peek();

            if (next == ' ')
                return token(token_type::TOKEN_OPERATOR, value);

            if (value != "-")
                throw std::runtime_error("ERROR: what.");

            // value = peak_consume();

            if (is_integer())
            {
                {
                    while (has_next() && is_integer())
                        value += peak_consume();

                    return token(token_type::TOKEN_INTEGER, value);
                }
            }
        }

        // Punctuator
        if (is_punctuator())
        {
            auto p = peek();
            value += peak_consume();
            if (p == '(')
                return token(token_type::TOKEN_P_L, value);
            if (p == ')')
                return token(token_type::TOKEN_P_R, value);
        }

        // Variable
        if (is_variable())
        {
            while (has_next() && is_variable())
                value += peak_consume();

            if (value == "print" || value == "config")
                return token(token_type::TOKEN_CALL, value);

            return token(token_type::TOKEN_VARIABLE, value);
        }

        return token(token_type::TOKEN_EOF, "");
    }

    auto lexer::is_integer() const -> bool { return std::isdigit(peek()); }
    auto lexer::is_whitespace() const -> bool { return std::isspace(peek()); }
    auto lexer::is_variable() const -> bool
    {
        static std::regex const variable_regex{"^[a-zA-Z_][a-zA-Z0-9_]*$"};
        return std::regex_match(std::string(1, peek()), variable_regex);
    }
    auto lexer::is_punctuator() const -> bool
    {
        std::regex operator_regex{"[()]"};

        return std::regex_match(std::string(1, peek()), operator_regex);
    }
    auto lexer::is_operator() const -> bool
    {
        static std::regex const punctuator_regex{"^[-+*/=]?$"};
        return std::regex_match(std::string(1, peek()), punctuator_regex);
    }

    auto lexer::has_next() const -> bool { return m_cursor < m_input.size(); }
    auto lexer::peek() const -> char { return m_input[m_cursor]; }
    auto lexer::peak_consume() -> char { return m_input[m_cursor++]; }
    auto lexer::consume() -> void { m_cursor++; }
    auto lexer::consume_space() -> void
    {
        while (has_next() && is_whitespace())
            consume();
    }

}