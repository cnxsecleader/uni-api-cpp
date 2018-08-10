FIND_PACKAGE(JSONCPP REQUIRED)
FIND_PACKAGE(JSONRPCCPP REQUIRED)
FIND_PACKAGE(CURL REQUIRED)

# Find header and source files
FILE(GLOB uniapi_header ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
FILE(GLOB uniapi_source ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# Set target libraries
ADD_LIBRARY(uniapi SHARED ${uniapi_source})
ADD_LIBRARY(uniapi_static STATIC ${uniapi_source})

# Set output name of static library
SET_TARGET_PROPERTIES(uniapi_static PROPERTIES OUTPUT_NAME uniapi)

# Link the library with json-rpc-cpp libs
TARGET_LINK_LIBRARIES(uniapi
                        ${CURL_LIBRARY}
                        ${JSONCPP_LIBRARY}
                        jsonrpccpp-common
                        jsonrpccpp-client)

TARGET_LINK_LIBRARIES(uniapi_static
                        ${CURL_LIBRARY}
                        ${JSONCPP_LIBRARY}
                        jsonrpccpp-common
                        jsonrpccpp-client)

# Set version settings
SET(VERSION_STRING ${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_VERSION})
SET_TARGET_PROPERTIES(uniapi uniapi_static PROPERTIES
    VERSION "${VERSION_STRING}"
    SOVERSION "${SO_VERSION}")

# Install to appropriate destinations
INSTALL(FILES ${uniapi_header} DESTINATION include/uniapi)

INSTALL(TARGETS uniapi uniapi_static
            LIBRARY DESTINATION lib
            ARCHIVE DESTINATION lib)
