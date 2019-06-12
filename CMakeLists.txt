cmake_minimum_required(VERSION 3.4.3)
project(gen8)

file(GLOB SOURCES_SRC src/*.cpp src/*.h)

add_subdirectory(llvm/llvm)

include_directories(${LLVM_INCLUDE_DIRS})
link_directories(${LLVM_LIBRARY_DIRS})
add_definitions(${LLVM_DEFINITIONS})

add_executable(gen8 ${SOURCES_SRC})

llvm_map_components_to_libnames(
  LLVM_COMPONENT_LIBS
  x86asmparser
  bitreader
  support
  mc
  option
  profiledata
)

target_link_libraries(
  gen8
  ${LLVM_COMPONENT_LIBS}
  clangAST
  clangASTMatchers
  clangAnalysis
  clangBasic
  clangDriver
  clangEdit
  clangFrontend
  clangLex
  clangParse
  clangRewrite
  clangRewriteFrontend
  clangSema
  clangSerialization
  clangTooling
)
