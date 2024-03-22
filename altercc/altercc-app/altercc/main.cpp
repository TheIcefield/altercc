#include <altercc/lexer/Lexer.hpp>

#include <iostream>
#include <fstream>
#include <vector>


void usage()
{
    std::cout << "altercc <file_name>\n";
}

int main(int argc, char **argv)
{
    std::vector<std::string> input_files{};
    std::string output_file = "a.out";
    bool dump_tokens = false;
    bool dump_ast = true;

    for (uint32_t i = 1; i < argc; i++)
    {
        std::string const arg = argv[i];
        if (arg == "-o")
        {
            output_file = argv[++i];
        }
        else if (arg == "--dump-tokens")
        {
            dump_tokens = true;
        }
        else if (arg == "--dump-ast")
        {
            dump_ast = true;
        }
        else
        {
            input_files.emplace_back(std::move(arg));
        }
    }

    if (input_files.empty())
    {
        std::cerr << "Input files are unspecified\n";
        usage();
        return -1;
    }

    for (auto &input_file: input_files)
    {
        std::cout << "Compiling \"" << input_file << "\"...\n";
        std::ifstream input(input_file);
        if (!input.is_open())
        {
            std::cerr << "Error: No such file: \"" << input_file << "\"\n";
            usage();
            return -1;
        }

        altercc::Lexer lexer(input, dump_tokens);
        auto const tokens = lexer.collect();

        altercc::Lexer::dump_tokens(std::cout, tokens);
    }

    return 0;
}
