#include <args.hxx>
#include <catch2/catch_all.hpp>

int main(int argc, char* argv[])
{
    Catch::Session session;

    args::ArgumentParser parser("This is a leetcode testing framework.", "This goes after the options.");
    args::HelpFlag help(parser, "help", "Display this help menu", {'h', "help"});
    args::ValueFlag<int> logLevel(parser, "logLevel", "log level flag", {'l', "log"}, -1);
    try {
        parser.ParseCLI(argc, argv);
    } catch (args::Error e) {
        // std::cerr << e.what() << std::endl;
        std::cerr << parser;
        int returnCode = session.applyCommandLine(1, argv);
        std::cout << returnCode << std::endl;
    }
    int numFailed = session.run();
    return numFailed;
}
