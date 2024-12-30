project('Tic Tac Toe', 'cpp', version: '0.0.1', default_options: ['cpp_std=c++17'])

inc_dir = include_directories('include')

subdir('src')

executable('ticTacToe', 
    main_src, 
    include_directories: inc_dir,
    link_with: tic_tac_toe_lib
)

# Tests
gtest = subproject('gtest')
subdir('tests')