# Install script for directory: /home/pomjak/Dropbox/VUT/4.semestr/IZG/project/libs/MealyMachine

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/pomjak/Dropbox/VUT/4.semestr/IZG/project/build/libs/MealyMachine/libMealyMachine.a")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/MealyMachine" TYPE FILE FILES "/home/pomjak/Dropbox/VUT/4.semestr/IZG/project/build/libs/MealyMachine/MealyMachine/mealymachine_export.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/MealyMachine" TYPE FILE FILES
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/project/libs/MealyMachine/src/MealyMachine/Fwd.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/project/libs/MealyMachine/src/MealyMachine/MapTransitionChooser.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/project/libs/MealyMachine/src/MealyMachine/MealyMachine.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/project/libs/MealyMachine/src/MealyMachine/TransitionChooser.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/project/libs/MealyMachine/src/MealyMachine/Exception.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/MealyMachine" TYPE FILE FILES
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/project/build/libs/MealyMachine/MealyMachine/MealyMachineConfig.cmake"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/project/build/libs/MealyMachine/MealyMachine/MealyMachineConfigVersion.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/MealyMachine/MealyMachineTargets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/MealyMachine/MealyMachineTargets.cmake"
         "/home/pomjak/Dropbox/VUT/4.semestr/IZG/project/build/libs/MealyMachine/CMakeFiles/Export/8a78f3cfc4e16014fa93791fc7915ae5/MealyMachineTargets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/MealyMachine/MealyMachineTargets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/MealyMachine/MealyMachineTargets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/MealyMachine" TYPE FILE FILES "/home/pomjak/Dropbox/VUT/4.semestr/IZG/project/build/libs/MealyMachine/CMakeFiles/Export/8a78f3cfc4e16014fa93791fc7915ae5/MealyMachineTargets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^()$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/MealyMachine" TYPE FILE FILES "/home/pomjak/Dropbox/VUT/4.semestr/IZG/project/build/libs/MealyMachine/CMakeFiles/Export/8a78f3cfc4e16014fa93791fc7915ae5/MealyMachineTargets-noconfig.cmake")
  endif()
endif()
