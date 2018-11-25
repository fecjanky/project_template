cmake_minimum_required(VERSION 3.1.3)

project("header only project template" VERSION 0.1 LANGUAGES CXX)

# Sample project for header only library

add_library(HeaderOnlyLib INTERFACE)

set(HEADERONLYLIB_CMAKE_LIB_DIR lib/cmake/HeaderOnlyLib)
set(HEADERONLYLIB_CMAKE_INSTALL_INCLUDE_DIR include/HeaderOnlyLib)
set(HEADERONLYLIB_CMAKE_INSTALL_SHARE_DIR share/HeaderOnlyLib)

target_include_directories(HeaderOnlyLib
  INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${HEADERONLYLIB_CMAKE_INSTALL_INCLUDE_DIR}>
)

# add visualizer to project that uses this project when MSVC is the generator
if(MSVC)
set(NATVIS_FILE HeaderOnlyLib.natvis)
target_sources(HeaderOnlyLib  
	INTERFACE 
		$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/visualizer/${NATVIS_FILE}>
		$<INSTALL_INTERFACE:${HEADERONLYLIB_CMAKE_INSTALL_SHARE_DIR}/${NATVIS_FILE}>
)
endif()


include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${PROJECT_BINARY_DIR}/HeaderOnlyLibConfigVersion.cmake"
    VERSION 0.1
    COMPATIBILITY AnyNewerVersion
)

# use standard fs layout for artifacts
install(TARGETS HeaderOnlyLib
    EXPORT HeaderOnlyLibTargets
    LIBRARY DESTINATION lib COMPONENT Runtime
    ARCHIVE DESTINATION lib COMPONENT Development
    RUNTIME DESTINATION bin COMPONENT Runtime
    PUBLIC_HEADER DESTINATION include COMPONENT Development
    BUNDLE DESTINATION bin COMPONENT Runtime
)

install(EXPORT HeaderOnlyLibTargets DESTINATION ${HEADERONLYLIB_CMAKE_LIB_DIR})

include(CMakePackageConfigHelpers)
configure_package_config_file(
    "${PROJECT_SOURCE_DIR}/cmake/HeaderOnlyLibConfig.cmake.in"
    "${PROJECT_BINARY_DIR}/HeaderOnlyLibConfig.cmake"
    INSTALL_DESTINATION ${HEADERONLYLIB_CMAKE_LIB_DIR}
)

install(FILES "${PROJECT_BINARY_DIR}/HeaderOnlyLibConfigVersion.cmake"
              "${PROJECT_BINARY_DIR}/HeaderOnlyLibConfig.cmake"
        DESTINATION ${HEADERONLYLIB_CMAKE_LIB_DIR})
		
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ DESTINATION ${HEADERONLYLIB_CMAKE_INSTALL_INCLUDE_DIR})

if(MSVC)
install(FILES  visualizer/${NATVIS_FILE} DESTINATION ${HEADERONLYLIB_CMAKE_INSTALL_SHARE_DIR})
endif()