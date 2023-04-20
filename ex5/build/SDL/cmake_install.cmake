# Install script for directory: /home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/build/SDL/libSDL2main.a")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/build/SDL/libSDL2.a")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2/SDL2mainTargets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2/SDL2mainTargets.cmake"
         "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/build/SDL/CMakeFiles/Export/f084604df1a27ef5b4fef7c7544737d1/SDL2mainTargets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2/SDL2mainTargets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2/SDL2mainTargets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2" TYPE FILE FILES "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/build/SDL/CMakeFiles/Export/f084604df1a27ef5b4fef7c7544737d1/SDL2mainTargets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^()$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2" TYPE FILE FILES "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/build/SDL/CMakeFiles/Export/f084604df1a27ef5b4fef7c7544737d1/SDL2mainTargets-noconfig.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2/SDL2staticTargets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2/SDL2staticTargets.cmake"
         "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/build/SDL/CMakeFiles/Export/f084604df1a27ef5b4fef7c7544737d1/SDL2staticTargets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2/SDL2staticTargets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2/SDL2staticTargets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2" TYPE FILE FILES "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/build/SDL/CMakeFiles/Export/f084604df1a27ef5b4fef7c7544737d1/SDL2staticTargets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^()$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2" TYPE FILE FILES "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/build/SDL/CMakeFiles/Export/f084604df1a27ef5b4fef7c7544737d1/SDL2staticTargets-noconfig.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2" TYPE FILE FILES
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/SDL2Config.cmake"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/build/SDL2ConfigVersion.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/SDL2" TYPE FILE FILES
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_assert.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_atomic.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_audio.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_bits.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_blendmode.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_clipboard.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_config_android.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_config_emscripten.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_config_iphoneos.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_config_macosx.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_config_minimal.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_config_os2.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_config_pandora.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_config_windows.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_config_winrt.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_copying.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_cpuinfo.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_egl.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_endian.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_error.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_events.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_filesystem.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_gamecontroller.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_gesture.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_haptic.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_hidapi.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_hints.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_joystick.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_keyboard.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_keycode.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_loadso.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_locale.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_log.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_main.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_messagebox.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_metal.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_misc.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_mouse.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_mutex.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_name.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_opengl.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_opengl_glext.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_opengles.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_opengles2.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_opengles2_gl2.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_opengles2_gl2ext.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_opengles2_gl2platform.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_opengles2_khrplatform.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_pixels.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_platform.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_power.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_quit.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_rect.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_render.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_rwops.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_scancode.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_sensor.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_shape.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_stdinc.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_surface.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_system.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_syswm.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_test.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_test_assert.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_test_common.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_test_compare.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_test_crc32.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_test_font.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_test_fuzzer.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_test_harness.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_test_images.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_test_log.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_test_md5.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_test_memory.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_test_random.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_thread.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_timer.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_touch.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_types.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_version.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_video.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/SDL_vulkan.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/begin_code.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/include/close_code.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/build/SDL/include/SDL_config.h"
    "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/build/SDL/include/SDL_revision.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/build/SDL/sdl2.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE PROGRAM FILES "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/build/SDL/sdl2-config")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/aclocal" TYPE FILE FILES "/home/pomjak/Dropbox/VUT/4.semestr/IZG/ex5/SDL/sdl2.m4")
endif()

