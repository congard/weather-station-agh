FILE(GLOB_RECURSE observer_sources
        "tulz/include/tulz/observer/*.h")

idf_component_register(SRCS ${observer_sources}
        INCLUDE_DIRS "tulz/include")