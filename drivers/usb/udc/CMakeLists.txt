set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

find_library(UDC_FOUND udc HINTS ${LIB_DIR})

if(NOT UDC_FOUND)
        message(FATAL_ERROR
                "Realtek library udc not found.\n"
                "Run the command below to download the necessary files:\n"
                "> west blobs fetch hal_realtek")
endif()

zephyr_include_directories(${INCLUDE_DIR})

add_library(udc_lib STATIC IMPORTED GLOBAL)

add_dependencies(
        udc_lib
        stm32wba_ll_lib
)
set_target_properties(udc_lib PROPERTIES IMPORTED_LOCATION ${LIB_DIR}/libudc.a)

set_target_properties(udc_lib PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ${INCLUDE_DIR}/)

target_link_libraries(app PUBLIC udc_lib)
