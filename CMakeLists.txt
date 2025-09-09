cmake_minimum_required(VERSION 3.10)
project(Bootcamp
        DESCRIPTION "C++ Bootcamp"
        LANGUAGES CXX)

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  if(CMAKE_CXX_COMPILER_VERSION MATCHES "^14.")
    message(STATUS "You're using ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
  else()
    message(WARNING "!! We recommend that you use clang-14 for this bootcamp. You're using ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}, a different version.")
  endif()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
  message(STATUS "You're using ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
else()
  message(WARNING "!! We recommend that you use clang-14 for this bootcamp. You're using ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}, which is not clang.")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Compiling move semantics/references executables
add_executable(references "1 - References and Move Semantics/references.cpp")
add_executable(move_semantics "1 - References and Move Semantics/move_semantics.cpp")
add_executable(move_constructors "1 - References and Move Semantics/move_constructors.cpp")

# Compiling templates executables
add_executable(templated_functions "2 - C++ Templates/templated_functions.cpp")
add_executable(templated_classes "2 - C++ Templates/templated_classes.cpp")

# Compiling misc executables
add_executable(wrapper_class "3 - Misc/wrapper_class.cpp")
add_executable(iterator "3 - Misc/iterator.cpp")
add_executable(namespaces "3 - Misc/namespaces.cpp")

# Compiling Containers executables
add_executable(vectors "4 - Containers/vectors.cpp")
add_executable(sets "4 - Containers/sets.cpp")
add_executable(unordered_maps "4 - Containers/unordered_maps.cpp")
add_executable(auto "4 - Containers/auto.cpp")

# Compiling Memory executables
add_executable(unique_ptr "5 - Memory/unique_ptr.cpp")
add_executable(shared_ptr "5 - Memory/shared_ptr.cpp")
