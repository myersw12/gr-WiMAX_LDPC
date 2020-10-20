# Locate WiMAX LDPC Library

message( "-- searching for WiMAX LDPC Library")

set( WiMAXLDPC_FOUND "NO" )

find_path( WiMAXLDPC_INCLUDE_DIR
  NAMES wimax_ldpc_lib/ldpc.h
  HINTS
  PATH_SUFFIXES include
  PATHS
  /usr/local/
)

find_library( WiMAXLDPC_LIBRARY
  NAMES wimax_ldpc_lib
  HINTS
  PATH_SUFFIXES lib64 lib
  PATHS
  /usr/local
)

if(WiMAXLDPC_LIBRARY)
set( WiMAXLDPC_FOUND "YES" )
endif(WiMAXLDPC_LIBRARY)

message( "-- WiMAXLDPC_INCLUDE_DIR is ${WiMAXLDPC_INCLUDE_DIR}" )
message( "-- WiMAXLDPC_LIBRARY is ${WiMAXLDPC_LIBRARY}" )

MARK_AS_ADVANCED( WiMAXLDPC_FOUND )
