project('RaylibTemplate', 'cpp',
  default_options: [
    'cpp_std=c++20',
    'buildtype=release',
    'optimization=2',
    'debug=false',
    'b_ndebug=if-release',
    'warning_level=3',
  ]
)

raylib_dep = dependency('raylib', method: 'pkg-config')
entt_dep = dependency('entt', method: 'pkg-config')

raygui_dir=include_directories('raygui/src')

executable('app',
  ['src/main.cpp','raygui/src/raygui.cpp'],
dependencies: [raylib_dep,entt_dep],
include_directories:raygui_dir)