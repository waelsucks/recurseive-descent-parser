#if !defined(LEXER_H_s)
#define LEXER_H_s

#include <string>
#include <regex>
#include <algorithm>

#include "token.hpp"

namespace cat
{
    class lexer
    {
    public:
        lexer(const std::string &input) : m_input(input), m_cursor(0){};
        ~lexer(){};

        auto tokenize() -> std::vector<token>;

    private:
        std::string m_input;
        std::size_t m_cursor;

    private:
        auto consume() -> void;
        auto consume_space() -> void;
        auto peak_consume() -> char;
        auto next() -> token;

    private:
        auto has_next() const -> bool;
        auto peek() const -> char;

        auto is_integer() const -> bool;
        auto is_whitespace() const -> bool;
        auto is_operator() const -> bool;
        auto is_punctuator() const -> bool;
        auto is_variable() const -> bool;
    };

} // namespace cat

#endif // LEXER_H_
