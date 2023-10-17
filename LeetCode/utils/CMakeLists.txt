
add_library(static-cxx-runtime INTERFACE IMPORTED GLOBAL)

# args
include(argparse.cmake)

# catch2
include(catch2.cmake)

# spdlog
include(spdlog.cmake)

# jasoncpp
include(nlohmannjson.cmake)

# yaml
include(yaml.cmake)