tic_tac_toe_test_srcs = [
    'TicTacToeTests.cpp'
    ,'BoardTableTests.cpp'
]


tic_tac_toe_test = executable('tic_tac_toe_test', 
    [tic_tac_toe_test_srcs, test_main], 
    include_directories : inc_dir,
    dependencies : [test_deps], 
    link_with : [test_dep_libs, tic_tac_toe_lib])

test('TicTacToeTest', tic_tac_toe_test)
