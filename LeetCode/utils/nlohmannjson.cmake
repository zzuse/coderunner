include(ExternalProject)

ExternalProject_Add(
    nlohmannjson_build
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.2
    UPDATE_COMMAND ""
    INSTALL_COMMAND ""
)

ExternalProject_Get_Property(nlohmannjson_build source_dir)
# message("source_dir = ${source_dir}")

add_library(nlohmannjson INTERFACE)
add_dependencies(nlohmannjson nlohmannjson_build)
set_target_properties(nlohmannjson PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${source_dir}/single_include/nlohmann/"
)