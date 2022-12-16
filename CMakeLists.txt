
# openssl
if (WIN32)
    add_subdirectory(openssl-cmake)
elseif (APPLE)
    add_subdirectory(openssl-cmake)
elseif (UNIX)
    add_subdirectory(openssl-cmake)
endif ()

# Set OpenSSL target names for Curl
add_library(OpenSSL::SSL STATIC IMPORTED)
add_library(OpenSSL::Crypto STATIC IMPORTED)
set_target_properties(OpenSSL::SSL PROPERTIES IMPORTED_LOCATION ${CMAKE_BINARY_DIR}/deps/openssl-cmake/usr/local/lib/libssl.a)
set_target_properties(OpenSSL::Crypto PROPERTIES IMPORTED_LOCATION ${CMAKE_BINARY_DIR}/deps/openssl-cmake/usr/local/lib/libcrypto.a)
set(OPENSSL_ROOT_DIR ${CMAKE_BINARY_DIR}/deps/openssl-cmake/usr/local)
set(OPENSSL_INCLUDE_DIR ${CMAKE_BINARY_DIR}/deps/openssl-cmake/usr/local/include)
# libcurl
set(HAVE_OPENSSL_CRYPTO_H TRUE CACHE INTERNAL "" FORCE)
set(HAVE_OPENSSL_ERR_H TRUE CACHE INTERNAL "" FORCE)
set(HAVE_OPENSSL_PEM_H TRUE CACHE INTERNAL "" FORCE)
set(HAVE_OPENSSL_RSA_H TRUE CACHE INTERNAL "" FORCE)
set(HAVE_OPENSSL_SSL_H TRUE CACHE INTERNAL "" FORCE)
set(HAVE_OPENSSL_X509_H TRUE CACHE INTERNAL "" FORCE)
set(HAVE_OPENSSL_RAND_H TRUE CACHE INTERNAL "" FORCE)
set(HAVE_RAND_STATUS TRUE CACHE INTERNAL "" FORCE)
set(HAVE_RAND_SCREEN FALSE CACHE INTERNAL "" FORCE)
set(HAVE_RAND_EGD FALSE CACHE INTERNAL "" FORCE)

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
    set(CURL_LIBRARY "-lcurl -lcrypto")
    include_directories(${CURL_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/include_mac)
elseif (UNIX)
    include_directories(lib_linux/)
    link_directories(include_linux/)
    set(CURL_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include_linux)
    set(CURL_LIBRARY "-lcurl  -lcrypto")
    include_directories(${CURL_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/include_linux)
endif ()

# Curl

add_library(pdm-network
        pdm-network.h
        pdm-network.cpp )

set(CURL_LIBRARIES ${CURL_LIBRARIES}
    ssl
    crypto
    )

target_compile_options ( pdm-network PRIVATE
    -m64
    -DCURL_STATICLIB
    -lcurl -lssl
)
if(WIN32)
    target_link_libraries(pdm-network ${CMAKE_CURRENT_SOURCE_DIR}/lib/libcurl.dll.a  ssl crypto ${CURL_LIBRARIES} )
elseif (APPLE)
    target_link_libraries(pdm-network ${CMAKE_CURRENT_SOURCE_DIR}/lib_mac/libcurl.a ${CURL_LIBRARIES} )
elseif (UNIX)
    target_link_libraries(pdm-network ${CMAKE_CURRENT_SOURCE_DIR}/lib_linux/libcurl.a ${CURL_LIBRARIES} )
endif ()


target_include_directories(pdm-network PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
