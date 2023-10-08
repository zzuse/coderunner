
add_library(static-cxx-runtime INTERFACE IMPORTED GLOBAL)

# catch2
include(catch2.cmake)

# spdlog
include(spdlog.cmake)

# jasoncpp
include(nlohmannjson.cmake)

# args
include(args.cmake)

# yaml
include(yaml.cmake)