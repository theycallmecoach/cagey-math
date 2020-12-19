project('cagey-math', 'cpp', 
  version: '0.0.1',
  default_options : ['cpp_std=c++17'],
)

incdir = include_directories('include')

gtest_dep = dependency(
  'gtest', 
  main : true, 
  required : false
)

vector_unit_tests_sources = [
  'test/Vector2Tests.cc',
  'test/Vector3Tests.cc',
  'test/Vector4Tests.cc',
  'test/VectorTests.cc',
]

vector_unit_test = executable(
  'cagey_math_vector_unit_test',
  vector_unit_tests_sources,
  include_directories : incdir, 
  dependencies : gtest_dep,
 )

test('vector unit tests', vector_unit_test)