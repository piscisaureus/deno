cmake_minimum_required(VERSION 3.4.3)
project(gen8)

file(GLOB SOURCES_SRC src/*.cpp src/*.h)
add_executable(gen8 ${SOURCES_SRC})

set(LLVM_ENABLE_PROJECTS clang CACHE STRING "")
set(LLVM_TARGETS_TO_BUILD X86 CACHE STRING "")

set(LLVM_ENABLE_BINDINGS OFF CACHE BOOL "")
set(LLVM_ENABLE_DIA_SDK OFF CACHE BOOL "")
set(LLVM_ENABLE_OCAMLDOC OFF CACHE BOOL "")

set(LLVM_INCLUDE_BENCHMARKS OFF CACHE BOOL "")
set(LLVM_INCLUDE_DOCS OFF CACHE BOOL "")
set(LLVM_INCLUDE_EXAMPLES OFF CACHE BOOL "")
set(LLVM_INCLUDE_GO_TESTS OFF CACHE BOOL "")
set(LLVM_INCLUDE_RUNTIMES OFF CACHE BOOL "")
set(LLVM_INCLUDE_TESTS OFF CACHE BOOL "")
set(LLVM_INCLUDE_UTILS OFF CACHE BOOL "")

add_subdirectory(llvm/llvm)

set(LLVM_INCLUDE_DIRS
  ${LLVM_SOURCE_DIR}/include
  ${LLVM_BINARY_DIR}/include
)
llvm_map_components_to_libnames(LLVM_LIBS
  Option
  Support
)

set(CLANG_INCLUDE_DIRS
  ${LLVM_EXTERNAL_CLANG_SOURCE_DIR}/include
  ${LLVM_BINARY_DIR}/tools/clang/include
)
set(CLANG_LIBS
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

target_include_directories(gen8 PRIVATE
  ${LLVM_INCLUDE_DIRS}
  ${CLANG_INCLUDE_DIRS}
)
target_link_libraries(gen8
  ${LLVM_LIBS}
  ${CLANG_LIBS}
)
