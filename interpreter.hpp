#if !defined(INTERPRETER_H_)
#define INTERPRETER_H_

#include <iostream>
#include <unordered_map>

#include "node.hpp"

namespace cat
{
    enum MODES
    {
        DEC,
        HEX,
        BIN
    };

    class interpreter
    {
    public:
        interpreter(std::ostream &output) : m_output(output), m_variables({}), m_mode(MODES::DEC){};
        ~interpreter(){};

        auto eval(node *node)                           -> int;
        auto eval_expression(node *node_to_evaluate)    -> int;

    private:
        std::unordered_map<std::string, std::int32_t> m_variables;

    private:
        std::ostream    &m_output;
        MODES           m_mode;
    };

}

#endif // INTERPRETER_H_
