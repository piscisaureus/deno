cls
rem add /LDd to build dll
clang-cl /std:c++17 /D_ITERATOR_DEBUG_LEVEL=0 v8.cpp D:\deno2\target\debug\obj\core\libdeno\libdeno.lib -fuse-ld=lld-link /MTd %* /link winmm.lib
