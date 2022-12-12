if (WIN32)
    include_directories(lib/)
    link_directories(include/)
    set(CURL_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
    set(CURL_LIBRARY "-lcurl -lcrypto")
    include_directories(${CURL_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/include)
elseif (APPLE)
    include_directories(lib_mac/)
    link_directories(include_mac/)
    set(CURL_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include_mac)
    set(CURL_LIBRARY "-lcurl")
    include_directories(${CURL_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/include_mac)
elseif (UNIX)
    include_directories(lib_linux/)
    link_directories(include_linux/)
    set(CURL_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include_linux)
    set(CURL_LIBRARY "-lcurl ")
    include_directories(${CURL_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/include_linux)
endif ()



add_library(pdm-network
        pdm-network.h
        pdm-network.cpp )
target_compile_options(
        pdm-network PRIVATE
        -m64

)
if(WIN32)
    target_link_libraries(pdm-network ${CMAKE_CURRENT_SOURCE_DIR}/lib/libcurl.dll.a ${CURL_LIBRARIES} )
elseif (APPLE)
    target_link_libraries(pdm-network ${CMAKE_CURRENT_SOURCE_DIR}/lib_mac/libcurl.a ${CURL_LIBRARIES} )
elseif (UNIX)
    target_link_libraries(pdm-network ${CMAKE_CURRENT_SOURCE_DIR}/lib_linux/libcurl.a ${CURL_LIBRARIES} )
endif ()


target_include_directories(pdm-network PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
