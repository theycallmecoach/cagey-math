vector_unit_tests_sources = [
  'Vector2Tests.cc',
#  'Vector3Tests.cc',
#  'Vector4Tests.cc',
#  'VectorTests.cc',
]

vector_unit_test = executable(
  'cagey_math_vector_unit_test',
  vector_unit_tests_sources,
  include_directories : incdir, 
  dependencies : gtest_dep,
 )

matrix_unit_tests_sources = [
  'Matrix22Tests.cc',
]

matrix_unit_test = executable(
  'cagey_math_matrix_unit_test',
  matrix_unit_tests_sources,
  include_directories : incdir, 
  dependencies : gtest_dep,
 )



test('vector unit tests', vector_unit_test)
test('matrix unit tests', matrix_unit_test)
