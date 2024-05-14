# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/gerald/systems/Edusat-RPI-Dev/rpi_edu_system/Squareline_build_files/SquareLine_Project/build/_deps/lv_drivers-src"
  "/home/gerald/systems/Edusat-RPI-Dev/rpi_edu_system/Squareline_build_files/SquareLine_Project/build/_deps/lv_drivers-build"
  "/home/gerald/systems/Edusat-RPI-Dev/rpi_edu_system/Squareline_build_files/SquareLine_Project/build/_deps/lv_drivers-subbuild/lv_drivers-populate-prefix"
  "/home/gerald/systems/Edusat-RPI-Dev/rpi_edu_system/Squareline_build_files/SquareLine_Project/build/_deps/lv_drivers-subbuild/lv_drivers-populate-prefix/tmp"
  "/home/gerald/systems/Edusat-RPI-Dev/rpi_edu_system/Squareline_build_files/SquareLine_Project/build/_deps/lv_drivers-subbuild/lv_drivers-populate-prefix/src/lv_drivers-populate-stamp"
  "/home/gerald/systems/Edusat-RPI-Dev/rpi_edu_system/Squareline_build_files/SquareLine_Project/build/_deps/lv_drivers-subbuild/lv_drivers-populate-prefix/src"
  "/home/gerald/systems/Edusat-RPI-Dev/rpi_edu_system/Squareline_build_files/SquareLine_Project/build/_deps/lv_drivers-subbuild/lv_drivers-populate-prefix/src/lv_drivers-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/gerald/systems/Edusat-RPI-Dev/rpi_edu_system/Squareline_build_files/SquareLine_Project/build/_deps/lv_drivers-subbuild/lv_drivers-populate-prefix/src/lv_drivers-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/gerald/systems/Edusat-RPI-Dev/rpi_edu_system/Squareline_build_files/SquareLine_Project/build/_deps/lv_drivers-subbuild/lv_drivers-populate-prefix/src/lv_drivers-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
