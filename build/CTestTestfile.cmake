# CMake generated Testfile for 
# Source directory: /home/mattia/pf/progetto_volterra
# Build directory: /home/mattia/pf/progetto_volterra/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if(CTEST_CONFIGURATION_TYPE MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test([=[progetto.t]=] "/home/mattia/pf/progetto_volterra/build/Debug/progetto.t")
  set_tests_properties([=[progetto.t]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/mattia/pf/progetto_volterra/CMakeLists.txt;53;add_test;/home/mattia/pf/progetto_volterra/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test([=[progetto.t]=] "/home/mattia/pf/progetto_volterra/build/Release/progetto.t")
  set_tests_properties([=[progetto.t]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/mattia/pf/progetto_volterra/CMakeLists.txt;53;add_test;/home/mattia/pf/progetto_volterra/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test([=[progetto.t]=] "/home/mattia/pf/progetto_volterra/build/RelWithDebInfo/progetto.t")
  set_tests_properties([=[progetto.t]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/mattia/pf/progetto_volterra/CMakeLists.txt;53;add_test;/home/mattia/pf/progetto_volterra/CMakeLists.txt;0;")
else()
  add_test([=[progetto.t]=] NOT_AVAILABLE)
endif()
