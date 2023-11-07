#if !defined(PARSER_H_)
#define PARSER_H_

#include <regex>

#include "token.hpp"
#include "node.hpp"

namespace cat
{
    class parser
    {
    public:
        parser(const std::vector<token> &tokens) : m_tokens(tokens), m_cursor(0), m_nodes({}){};
        ~parser(){};

        auto parse() -> void;

        auto program() -> std::vector<node *>;

    private:
        auto parse_statement() -> node *;
        auto parse_expression() -> node *;
        auto parse_term_expression() -> node *;
        auto parse_factor_expression() -> node *;

        auto parse_assignment_expression() -> node *;
        auto parse_call_expression() -> node *;

    private:
        auto has_next() const -> bool;
        auto peek() const -> token;
        auto peek_next(int i) const -> std::optional<token>;
        auto consume() -> token;

    private:
        std::size_t m_cursor;
        std::vector<node *> m_nodes;
        std::vector<token> m_tokens;
    };

} // namespace cat

#endif // PARSER_H_
