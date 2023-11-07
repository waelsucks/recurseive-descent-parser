#include <iostream>
#include <fstream>

#include "lexer.hpp"
#include "parser.hpp"
#include "interpreter.hpp"
#include "node.hpp"

int main(int argc, char **argv)
{
    // if (argc < 2)
    // {
    //     std::cerr << "Please provide a file name." << std::endl;
    //     return 1;
    // }

    // std::ifstream file(argv[1]);
    std::ifstream file("/Users/waelmahrous/Desktop/Code/lab6/hello.cat");
    if (!file)
    {
        std::cerr << "Could not open file." << std::endl;
        return 1;
    }

    std::string input;
    for (std::string line; std::getline(file, line);)
    {
        input += line + '\n';
    }

    cat::lexer lexer(input);
    auto tokens = lexer.tokenize();

    cat::parser parser(tokens);
    parser.parse();

    auto nodes = parser.program();

    cat::interpreter interpreter(std::cout);

    for (cat::node *node : nodes)
    {
        interpreter.eval(node);
    }

    return 0;
}