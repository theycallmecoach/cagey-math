
incdir = include_directories('../include')

gtest_dep = dependency('gtest', main : true, required: true)

test_sources = ['DegreeTests.cc', 'Vector2Tests.cc', 'Vector3Tests.cc', 'VectorTests.cc', 'MatrixTests.cc']

e = executable('cagey-math-test', test_sources, include_directories : incdir, dependencies : [gtest_dep])
test('gtest test', e)
