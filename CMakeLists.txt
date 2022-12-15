
add_library(pdm-network
        pdm-network.h
        pdm-network.cpp )

target_compile_options(
        pdm-network PRIVATE
        -m64
)

target_include_directories(pdm-network PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/asio/asio/include)
