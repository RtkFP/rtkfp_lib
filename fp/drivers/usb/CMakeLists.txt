set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../zephyr/blobs/fp/drivers)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

find_library(UDC_FOUND udc HINTS ${LIB_DIR})

if(NOT UDC_FOUND)
        message(FATAL_ERROR
                "Realtek library udc not found in ${LIB_DIR}.\n"
                "Run the command below to download the necessary files:\n"
                "> west blobs fetch hal_realtek")
endif()

zephyr_include_directories(${INCLUDE_DIR})

zephyr_link_libraries(${LIB_DIR}/libudc.a)
