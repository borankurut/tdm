project(
  'tdm',
  'cpp',
  version: '0.1.0',
  default_options: [
    'cpp_std=c++17',
    'buildtype=debug',
    'b_pch=false', # disable Meson’s experimental PCH support
  ],
)

# ——— Global compiler flags ——————————————————————
# ensure position-independent code
# add_project_arguments('-fPIC', language: 'cpp')

# define debug/release macros
if get_option('buildtype') == 'debug'
  add_project_arguments('-DDEBUG', language: 'cpp')
else
  add_project_arguments('-DRELEASE', language: 'cpp')
endif

# ——— Include dirs ————————————————————————————
inc = include_directories('include')

# ——— Main library ——————————————————————————
lib_sources = files(
  'src/euler.cpp',
  'src/mat2.cpp',
  'src/mat3.cpp',
  'src/mat4.cpp',
  'src/polar2.cpp',
  'src/polar3.cpp',
  'src/quaternion.cpp',
  'src/vec2.cpp',
  'src/vec3.cpp',
  'src/vec4.cpp',
)

math_lib = static_library(
  'math',
  lib_sources,
  include_directories: inc,
  install: false, # we don’t install the static library by default
)

# ——— Examples —————————————————————————————
if get_option('build_examples')
  executable(
    'main',
    'examples/main.cpp',
    include_directories: inc,
    link_with: math_lib,
    install: true,
  )
endif

# ——— Tests (Catch2 via WrapDB) ———————————————————
if get_option('build_tests')

  catch2_dep = dependency(
    'catch2-with-main',
    default_options: ['tests=false'],
    fallback: ['catch2', 'catch2_with_main_dep'],
  )

  test_sources = files(
    'tests/test_common_math.cpp',
    'tests/test_euler.cpp',
    'tests/test_mat2.cpp',
    'tests/test_mat3.cpp',
    'tests/test_mat4.cpp',
    'tests/test_polar2.cpp',
    'tests/test_polar3.cpp',
    'tests/test_vectors.cpp',
  )

  math_tests = executable(
    'math_tests',
    test_sources,
    include_directories: inc,
    dependencies: [catch2_dep],
    link_with: math_lib,
  )

  test(
    'math_tests',
    math_tests,
    args: ['--reporter', 'compact'],
  )
endif

tdm_dep = declare_dependency(link_with: math_lib, include_directories: inc)
