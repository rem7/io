make_build_bundle(_build)

set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/_build/dll)

generate_ioinit(TEST)

# Our library sources.
set(SRCS
	"${CMAKE_CURRENT_SOURCE_DIR}/source/IoTEST.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/source/IoTESTInit.c"
)

# Now build the shared library
add_library(IoTEST SHARED ${SRCS})
add_dependencies(IoTEST iovmall)
target_link_libraries(IoTEST iovmall)
set_target_properties(IoTEST PROPERTIES LINK_FLAGS "-Wl,-Map=iotest.map")
#target_link_libraries(IoTEST)
#set_target_properties(IoTEST PROPERTIES LINK_FLAGS "-Wl,-Map=iotest.map -L${CMAKE_BINARY_DIR}/_build/dll/ -liovmall")

# Install the addon to our global addons hierarchy.
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/io/addons)
install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/_build DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/io/addons/TEST)

