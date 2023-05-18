
# openssl
#if (WIN32)
#    add_subdirectory(openssl-cmake)
#elseif (APPLE)
#    add_subdirectory(openssl-cmake)
#elseif (UNIX)
#    add_subdirectory(openssl-cmake)
#endif ()

# Set OpenSSL target names for Curl
add_library(OpenSSL::SSL STATIC IMPORTED)
add_library(OpenSSL::Crypto STATIC IMPORTED)
set_target_properties(OpenSSL::SSL PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/local/lib/libssl.a)
set_target_properties(OpenSSL::Crypto PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/local/lib/libcrypto.a)
set(OPENSSL_ROOT_DIR ${CMAKE_CURRENT_DIR}/lib/local)
set(OPENSSL_INCLUDE_DIR ${CMAKE_CURRENT_DIR}/lib/local/include)
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

# static curl
#SET(CMAKE_FIND_LIBRARY_SUFFIXES .lib .a ${CMAKE_FIND_LIBRARY_SUFFIXES})
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
#    ssl
#    crypto
    OpenSSL::SSL
    OpenSSL::Crypto
    )

target_compile_options ( pdm-network PRIVATE
    -m64
)
if(WIN32)
    target_link_libraries(pdm-network
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/libcurl.dll.a
        ${CURL_LIBRARIES} )
    set(DIR_NAME_PDM_NETWORK "")

    target_include_directories(pdm-network PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
            ${CMAKE_CURRENT_SOURCE_DIR}/lib${DIR_NAME_PDM_NETWORK}/
            ${CMAKE_CURRENT_SOURCE_DIR}/lib/local/lib/)

elseif (APPLE)
    target_link_libraries(pdm-network ${CMAKE_CURRENT_SOURCE_DIR}/lib_mac/libcurl.a ${CURL_LIBRARIES} )
    set(DIR_NAME_PDM_NETWORK "_mac")

    target_include_directories(pdm-network PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
            ${CMAKE_CURRENT_SOURCE_DIR}/lib${DIR_NAME_PDM_NETWORK}/
            ${CMAKE_CURRENT_SOURCE_DIR}/lib_mac/local/lib/)
elseif (UNIX)
    target_link_libraries(pdm-network ${CMAKE_CURRENT_SOURCE_DIR}/lib_linux/libcurl.a ${CURL_LIBRARIES} )
    set(DIR_NAME_PDM_NETWORK "_linux")

    target_include_directories(pdm-network PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
            ${CMAKE_CURRENT_SOURCE_DIR}/lib${DIR_NAME_PDM_NETWORK}/
            ${CMAKE_CURRENT_SOURCE_DIR}/lib/local/lib/)
endif ()


