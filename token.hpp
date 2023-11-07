#if !defined(TOKEN_H_)
#define TOKEN_H_

#include <string>

namespace cat
{
    enum token_type
    {
        TOKEN_EOF,
        TOKEN_CALL,
        TOKEN_INTEGER,
        TOKEN_VARIABLE,
        TOKEN_OPERATOR,
        TOKEN_ASSIGNMENT,
        TOKEN_P_L,
        TOKEN_P_R,
        TOKEN_WHITESPACE,
        TOKEN_NEWLINE,
        TOKEN_UNKNOWN,
        TOKEN_ARGUMENT
    };

    class token
    {
    public:
        token(token_type type, const std::string &value) : type(type), value(value){};
        ~token(){};

    public:
        std::string value;
        token_type type;
    };
}; // namespace cat

#endif // TOKEN_H_
