#include "common.h"
#include "include/argparse/argparse.hpp"
#include <catch2/catch_all.hpp>

int main(int argc, char* argv[])
{
    argparse::ArgumentParser program("leetcoder");

    program.add_argument("-l", "--loglevel").default_value(0).scan<'i', int>();
    program.add_argument("catchcase").remaining();

    try {
        program.parse_args(argc, argv);
    } catch (const std::runtime_error& err) {
        std::cerr << err.what() << std::endl;
        std::cerr << program;
        std::exit(1);
    }
    auto loglevel = program.get<int>("loglevel");
    set_log_config(loglevel);
    spdlog::info("Log Level after set: {}", loglevel);

    try {
        auto catch_cases = program.get<std::vector<std::string>>("catchcase");
        std::cout << catch_cases.size() << " test provided" << std::endl;
        std::string test_name = catch_cases[0];
        std::string test_report = catch_cases[1];
        char* args[] = {(char*)"leetcoder", (char*)test_name.c_str(), (char*)test_report.c_str()};
        Catch::Session session;
        session.applyCommandLine(sizeof(args) / sizeof(args[0]), args);
        session.run();
    } catch (std::logic_error& e) {
        std::cout << "No test provided" << std::endl;
    }

    return 0;
}
