#include <catch2/catch_all.hpp>

int main(int argc, char* argv[])
{
    int loglevel = 0;
    Catch::Session session;
    using namespace Catch::Clara;
    auto cli = session.cli() | Opt(loglevel, "loglevel")["-l"]["--loglevel"]("log level");
    session.cli(cli);
    int returnCode = session.applyCommandLine(argc, argv);
    if (returnCode != 0) return returnCode;
    session.run();
    return 0;
}
