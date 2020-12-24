project('cagey-math', 'cpp', 
  version: '0.0.1',
  default_options : ['cpp_std=c++17'],
)

gtest_proj = subproject('gtest')
gtest_dep = gtest_proj.get_variable('gtest_main_dep')

incdir = include_directories('include')

subdir('test')
subdir('doc')
