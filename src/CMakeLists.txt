

set(CMAKE_CXX_STANDARD 17)

add_executable(headerify main.cpp)
target_compile_features(headerify PUBLIC cxx_std_17)
target_link_libraries(headerify stdc++fs)