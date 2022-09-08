#
# Copyright 2013-2021 Software Radio Systems Limited
#
# By using this file, you agree to the terms and conditions set
# forth in the LICENSE file which can be found at the top level of
# the distribution.
#

# - Try to find polarssl
#
# Once done this will define
#  POLARSSL_FOUND        - System has polarssl
#  POLARSSL_INCLUDE_DIRS - The polarssl include directories
#  POLARSSL_LIBRARIES    - The polarssl library

find_package(PkgConfig REQUIRED)
pkg_check_modules(PC_POLARSSL polarssl)

find_path(
    POLARSSL_INCLUDE_DIRS
    NAMES polarssl/version.h
    HINTS $ENV{POLARSSL_DIR}/include
          ${PC_POLARSSL_INCLUDEDIR}
          ${CMAKE_INSTALL_PREFIX}/include
    PATHS /usr/local/include
          /usr/include
)

find_library(
    POLARSSL_LIBRARIES
    NAMES polarssl
    HINTS $ENV{POLARSSL_DIR}/lib
          ${PC_POLARSSL_LIBDIR}
          ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
    PATHS /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

find_library(
    POLARSSL_STATIC_LIBRARIES
    NAMES libpolarssl.a
    HINTS $ENV{POLARSSL_DIR}/lib
          ${PC_POLARSSL_LIBDIR}
          ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
    PATHS /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

message(STATUS "POLARSSL LIBRARIES: " ${POLARSSL_LIBRARIES})
message(STATUS "POLARSSL STATIC LIBRARIES: " ${POLARSSL_STATIC_LIBRARIES})
message(STATUS "POLARSSL INCLUDE DIRS: " ${POLARSSL_INCLUDE_DIRS})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Polarssl DEFAULT_MSG POLARSSL_LIBRARIES POLARSSL_INCLUDE_DIRS)
mark_as_advanced(POLARSSL_STATIC_LIBRARIES POLARSSL_LIBRARIES POLARSSL_INCLUDE_DIRS)
