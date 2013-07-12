# - Try to find Hunspell
# Once done this will define
#
#  HUNSPELL_FOUND - system has Hunspell
#  HUNSPELL_INCLUDE_DIRS - the Hunspell include directory
#  HUNSPELL_LIBRARIES - Link these to use Hunspell
#  HUTSPELL_DEFINITIONS - Compiler switches required for using Hunspell
#
#  Copyright (c) 2007 Arne Schmitz <arne.schmitz@gmx.net>
#
#  Redistribution and use is allowed according to the terms of the New
#  BSD license.
#  For details see the accompanying COPYING-CMAKE-SCRIPTS file.
#

if(WIN32 AND NOT CYGWIN AND NOT MSYS)
  set(HUNSPELL_FIND_STYLE "win32")
else()
  if(UNIX OR MSYS)
    set(HUNSPELL_FIND_STYLE "unix")
  endif()
endif()

if(HUNSPELL_LIBRARIES AND HUNSPELL_INCLUDE_DIRS)
  # in cache already
  set(HUNSPELL_FOUND TRUE)
else(HUNSPELL_LIBRARIES AND HUNSPELL_INCLUDE_DIRS)
  if(WIN32 AND NOT CYGWIN AND NOT MSYS)
    set(HUNSPELL_FIND_STYLE "win32")
  else()
    if(UNIX OR MSYS)
      set(HUNSPELL_FIND_STYLE "unix")
    endif()
  endif()

  if(HUNSPELL_FIND_STYLE STREQUAL "win32")
    find_path(HUNSPELL_ROOT_DIR
      NAMES
        include/hunspell.hxx
      PATHS
        ENV HUNSPELL_ROOT_DIR
        C:/
        D:/
        ENV ProgramFiles
      PATH_SUFFIXES
        hunspell-1.3.2
    )

    find_library(HUNSPELL_LIBRARY
      NAMES
        libhunspell
      PATHS
        ENV HUNSPELL_ROOT_DIR
        C:/
        D:/
        ENV ProgramFiles
      PATH_SUFFIXES
        hunspell-1.3.2/lib
    )
  endif()

  if(HUNSPELL_FIND_STYLE STREQUAL "unix")
    find_path(HUNSPELL_INCLUDE_DIR
      NAMES
        hunspell/hunspell.hxx
      PATHS
        /usr/include
        /usr/local/include
        /opt/local/include
        /sw/include
    )

    find_library(HUNSPELL_LIBRARY
      NAMES
        hunspell
      PATHS
        /usr/lib
        /usr/local/lib
        /opt/local/lib
        /sw/lib
    )
  endif()

  set(HUNSPELL_INCLUDE_DIRS
    ${HUNSPELL_INCLUDE_DIR}
  )
  set(HUNSPELL_LIBRARIES
    ${HUNSPELL_LIBRARY}
  )

  if (HUNSPELL_INCLUDE_DIRS AND HUNSPELL_LIBRARIES)
     set(HUNSPELL_FOUND TRUE)
  endif (HUNSPELL_INCLUDE_DIRS AND HUNSPELL_LIBRARIES)

  if (HUNSPELL_FOUND)
    if (NOT hunspell_FIND_QUIETLY)
      message(STATUS "Found Hunspell: ${HUNSPELL_LIBRARIES}")
    endif (NOT hunspell_FIND_QUIETLY)
  else (HUNSPELL_FOUND)
    if (hunspell_FIND_REQUIRED)
      message(FATAL_ERROR "Could not find Hunspell")
    endif (hunspell_FIND_REQUIRED)
  endif (HUNSPELL_FOUND)

  # show the HUNSPELL_INCLUDE_DIRS and HUNSPELL_LIBRARIES variables only in the advanced view
  mark_as_advanced(HUNSPELL_INCLUDE_DIRS HUNSPELL_LIBRARIES)
endif(HUNSPELL_LIBRARIES AND HUNSPELL_INCLUDE_DIRS)
