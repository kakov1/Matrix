add_executable(main main.cpp)

target_include_directories(main PUBLIC ../inc/)
target_compile_features(main PRIVATE cxx_std_23) 