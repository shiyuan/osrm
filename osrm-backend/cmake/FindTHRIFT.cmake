# Locate THRIFT library
# This module defines
#  THRIFT_FOUND, if false, do not try to link to libthrift
#  THRIFT_LIBRARY
#  THRIFT_INCLUDE_DIR, where to find Thrift.h
#


IF( NOT THRIFT_FIND_QUIETLY )
    MESSAGE(STATUS "Looking for THRIFT...")
ENDIF()

FIND_PATH(THRIFT_INCLUDE_DIR Thrift.h
  HINTS
  $ENV{THRIFT_DIR}
  PATH_SUFFIXES thrift include/thirft/thrift include/thrift include
  PATHS
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local
  /usr
  /opt/local # DarwinPorts
  /opt
)

FIND_LIBRARY(THRIFT_LIBRARY
  NAMES thrift thrift_debug
  HINTS
  $ENV{THRIFT_DIR}
  PATH_SUFFIXES lib64 lib
  PATHS
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local
  /usr
  /opt/local
  /opt
)

INCLUDE(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set THRIFT_FOUND to TRUE if
# all listed variables are TRUE
FIND_PACKAGE_HANDLE_STANDARD_ARGS(THRIFT  DEFAULT_MSG  THRIFT_LIBRARY THRIFT_INCLUDE_DIR)

IF( NOT THRIFT_FIND_QUIETLY )
    IF( THRIFT_FOUND )
        MESSAGE(STATUS "Found THRIFT: ${THRIFT_LIBRARY}" )
    ENDIF()
ENDIF()

MARK_AS_ADVANCED(THRIFT_INCLUDE_DIR THRIFT_LIBRARY)
