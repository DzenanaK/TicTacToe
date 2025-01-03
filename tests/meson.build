gtest_dep = gtest.get_variable('gtest_dep')
test_main = files('test_main.cpp')

test_deps = [
    gtest_dep
]

subdir('TicTacToe')

# This executable contains all the tests
all_tests = executable('all_tests', 
    test_main, 
    include_directories : inc_dir, 
    dependencies : test_deps
)