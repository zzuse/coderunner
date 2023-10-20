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
    std::cout << "Log Level" << loglevel << std::endl;

    try {
        auto catch_cases = program.get<std::vector<std::string>>("catchcase");
        std::cout << catch_cases.size() << " test provided" << std::endl;
        char* args[] = {"leetcoder", "Factorials are computed"};
        Catch::Session session;
        session.applyCommandLine(2, args);
        int numFailed = session.run();
    } catch (std::logic_error& e) {
        std::cout << "No test provided" << std::endl;
    }

    return 0;
}
