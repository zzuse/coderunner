#include <catch2/catch_all.hpp>
#include <include/argparse.hpp>

int main(int argc, char* argv[])
{
    Catch::Session session;

    int returnCode = session.applyCommandLine(argc, argv);
    std::cout << returnCode << std::endl;
    int numFailed = session.run();
    std::cerr << numFailed;
    return 0;
}
