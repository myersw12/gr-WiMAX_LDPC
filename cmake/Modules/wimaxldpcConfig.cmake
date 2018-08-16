INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_WIMAXLDPC wimaxldpc)

FIND_PATH(
    WIMAXLDPC_INCLUDE_DIRS
    NAMES wimaxldpc/api.h
    HINTS $ENV{WIMAXLDPC_DIR}/include
        ${PC_WIMAXLDPC_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    WIMAXLDPC_LIBRARIES
    NAMES gnuradio-wimaxldpc
    HINTS $ENV{WIMAXLDPC_DIR}/lib
        ${PC_WIMAXLDPC_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(WIMAXLDPC DEFAULT_MSG WIMAXLDPC_LIBRARIES WIMAXLDPC_INCLUDE_DIRS)
MARK_AS_ADVANCED(WIMAXLDPC_LIBRARIES WIMAXLDPC_INCLUDE_DIRS)

