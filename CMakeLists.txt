
# openssl
#if (WIN32)
#    add_subdirectory(openssl-cmake)
#elseif (APPLE)
#    add_subdirectory(openssl-cmake)
#elseif (UNIX)
#    add_subdirectory(openssl-cmake)
#endif ()
if(APPLE)
#    list(APPEND CMAKE_PREFIX_PATH "/usr/local/opt")
#    list(APPEND CMAKE_PREFIX_PATH /usr/local/opt/curl )
#
#    set(OPENSSL_ROOT_DIR /usr/local/opt/openssl@3)
#    set(Brotli_DIR /usr/local/opt/brotli)
    find_package(OpenSSL REQUIRED)
    include_directories(${OPENSSL_INCLUDE_DIR})
#add_library(OpenSSL::SSL STATIC IMPORTED)
#add_library(OpenSSL::Crypto STATIC IMPORTED)
#set_target_properties(OpenSSL::SSL PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib_mac/local/lib/libssl.a)
#set_target_properties(OpenSSL::Crypto PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib_mac/local/lib/libcrypto.a)

elseif(UNIX)
set_target_properties(OpenSSL::SSL PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib_linux/local/lib/libssl.a)
set_target_properties(OpenSSL::Crypto PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib_linux/local/lib/libcrypto.a)
else()

# Set OpenSSL target names for Curl
add_library(OpenSSL::SSL STATIC IMPORTED)
add_library(OpenSSL::Crypto STATIC IMPORTED)
set_target_properties(OpenSSL::SSL PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/local/lib/libssl.a)
set_target_properties(OpenSSL::Crypto PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/local/lib/libcrypto.a)
endif()




# static curl
#SET(CMAKE_FIND_LIBRARY_SUFFIXES .lib .a ${CMAKE_FIND_LIBRARY_SUFFIXES})
if (WIN32)
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
    include_directories(lib/)
    link_directories(include/ )
    set(CURL_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
    set(CURL_LIBRARY "-lcurl -lcrypto")
    include_directories(${CURL_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/include)
elseif (APPLE)
    find_package(CURL REQUIRED)
#    include_directories(lib_mac/)
#    link_directories(include/ ${OPENSSL_INCLUDE_DIR})
#    set(CURL_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include_mac)
#    set(CURL_LIBRARY "-lcurl -lcrypto")
    include_directories(${CURL_INCLUDE_DIR} )
elseif (UNIX)
    include_directories(lib_linux/)
    link_directories(include_linux/)
    set(CURL_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include_linux)
    set(CURL_LIBRARY "-lcurl  -lssl -lcrypto")
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
#    # ZLIB
#    find_path(ZLIB_INCLUDE_DIR NAMES zlib.h PATHS /usr/local/opt/zlib/include)
#    find_library(ZLIB_LIBRARY NAMES z PATHS /usr/local/opt/zlib/lib)
#
#    # Brotli
#    find_path(BROTLI_INCLUDE_DIR NAMES brotli/encode.h PATHS /usr/local/opt/brotli/include)
#    find_library(BROTLI_ENC_LIBRARY NAMES brotlienc PATHS /usr/local/opt/brotli/lib)
#    find_library(BROTLI_DEC_LIBRARY NAMES brotlidec PATHS /usr/local/opt/brotli/lib)
#    find_library(BROTLI_COMMON_LIBRARY NAMES brotlicommon PATHS /usr/local/opt/brotli/lib)
#
#    # Openldap
#    find_path(LDAP_INCLUDE_DIR NAMES ldap.h PATHS /usr/local/opt/openldap/include)
#    find_library(LDAP_LIBRARY NAMES ldap PATHS /usr/local/opt/openldap/lib)
#    find_library(LBER_LIBRARY NAMES lber PATHS /usr/local/opt/openldap/lib)
#
#    # ZSTD
#    find_path(ZSTD_INCLUDE_DIR NAMES zstd.h PATHS /usr/local/opt/zstd/include)
#    find_library(ZSTD_LIBRARY NAMES zstd PATHS /usr/local/opt/zstd/lib)

    target_link_libraries(pdm-network
            OpenSSL::SSL OpenSSL::Crypto
#            ${CMAKE_CURRENT_SOURCE_DIR}/lib_mac/libcurl.a
            ${CURL_LIBRARIES}
#            ${ZLIB_LIBRARY}
#            ${BROTLI_ENC_LIBRARY} ${BROTLI_DEC_LIBRARY} ${BROTLI_COMMON_LIBRARY}
#            ${LDAP_LIBRARY} ${LBER_LIBRARY}
#            ${ZSTD_LIBRARY}
            )
    set(DIR_NAME_PDM_NETWORK "_mac")
    message(STATUS "MACOS build ${CMAKE_CURRENT_SOURCE_DIR}/lib${DIR_NAME_PDM_NETWORK}/")

    target_include_directories(pdm-network PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
            ${CURL_INCLUDE_DIRS}
#            ${CMAKE_CURRENT_SOURCE_DIR}/lib${DIR_NAME_PDM_NETWORK}/
#            ${CMAKE_CURRENT_SOURCE_DIR}/lib_mac/local/lib/
#            ${ZLIB_INCLUDE_DIR}
#            ${BROTLI_INCLUDE_DIR}
#            ${LDAP_INCLUDE_DIR}
#            ${ZSTD_INCLUDE_DIR}
            )
    # Check if each library and include directory exists
    if(NOT EXISTS ${ZLIB_INCLUDE_DIR})
        message(FATAL_ERROR "ZLIB include directory not found: ${ZLIB_INCLUDE_DIR}")
    endif()

    # Include the found directories
    include_directories(${ZLIB_INCLUDE_DIR} ${BROTLI_INCLUDE_DIR} ${LDAP_INCLUDE_DIR} ${ZSTD_INCLUDE_DIR})

    # Check if each library exists
    foreach(lib ${ZLIB_LIBRARY} ${BROTLI_ENC_LIBRARY} ${BROTLI_DEC_LIBRARY} ${BROTLI_COMMON_LIBRARY} ${LDAP_LIBRARY} ${LBER_LIBRARY} ${ZSTD_LIBRARY})
        if(NOT EXISTS ${lib})
            message(FATAL_ERROR "Library not found: ${lib}")
        endif()
    endforeach()

    # Link the libraries to your target
    target_link_libraries(pdm-network
            ${CMAKE_CURRENT_SOURCE_DIR}/lib_mac/libcurl.a
            ${CURL_LIBRARIES}
            ${ZLIB_LIBRARY}
            ${BROTLI_ENC_LIBRARY} ${BROTLI_DEC_LIBRARY} ${BROTLI_COMMON_LIBRARY}
            ${LDAP_LIBRARY} ${LBER_LIBRARY}
            ${ZSTD_LIBRARY}
            )
elseif (UNIX)
    target_link_libraries(pdm-network ${CMAKE_CURRENT_SOURCE_DIR}/lib_linux/libcurl.a ${CURL_LIBRARIES} )
    set(DIR_NAME_PDM_NETWORK "_linux")

    target_include_directories(pdm-network PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
            ${CMAKE_CURRENT_SOURCE_DIR}/lib${DIR_NAME_PDM_NETWORK}/
            ${CMAKE_CURRENT_SOURCE_DIR}/lib/local/lib/)
endif ()


