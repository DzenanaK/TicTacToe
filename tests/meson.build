all_test_deps = []
all_test_dep_libs = []
project_test_sources = []

gtest_dep = gtest.get_variable('gtest_dep')
test_main = files('test_main.cpp')

test_deps = [
    gtest_dep
]

test_dep_libs = [
]

subdir('TicTacToe')

# This executable contains all the tests
project_test_sources += test_main
all_test_deps += test_deps
all_test_dep_libs += test_dep_libs

all_tests = executable('all_tests', 
    project_test_sources, 
    include_directories : inc_dir, 
    dependencies : all_test_deps, 
    link_with : all_test_dep_libs)