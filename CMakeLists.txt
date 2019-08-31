cmake_minimum_required(VERSION 3.4.3)
project(gen9)

set(LLVM_ENABLE_PROJECTS clang CACHE STRING "")
set(LLVM_TARGETS_TO_BUILD X86 CACHE STRING "")

set(LLVM_INCLUDE_TESTS ON CACHE BOOL "")
set(LLVM_INCLUDE_UTILS ON CACHE BOOL "")

set(LLVM_ENABLE_BINDINGS OFF CACHE BOOL "")
set(LLVM_ENABLE_DIA_SDK OFF CACHE BOOL "")
set(LLVM_ENABLE_OCAMLDOC OFF CACHE BOOL "")

set(LLVM_INCLUDE_BENCHMARKS OFF CACHE BOOL "")
set(LLVM_INCLUDE_DOCS OFF CACHE BOOL "")
set(LLVM_INCLUDE_EXAMPLES OFF CACHE BOOL "")
set(LLVM_INCLUDE_GO_TESTS OFF CACHE BOOL "")
set(LLVM_INCLUDE_RUNTIMES OFF CACHE BOOL "")

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
  clangIndex
  clangLex
  clangParse
  clangRewrite
  clangRewriteFrontend
  clangSema
  clangSerialization
  clangTooling
)
