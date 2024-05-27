FILE(GLOB_RECURSE observer_sources
        "tulz/include/tulz/observer/*.h")

FILE(GLOB_RECURSE container_sources
        "tulz/include/tulz/container/*.h")

idf_component_register(SRCS
        ${observer_sources}
        ${container_sources}
        INCLUDE_DIRS "tulz/include")