project(
  'strike',
  'cpp',
  version : '0.1',
  meson_version : '>= 1.3.0',
  default_options : ['warning_level=3', 'cpp_std=c++23'],
)

dependencies = [
  dependency('wlroots-0.19', version: ['>=0.19.0', '<0.20.0'], required: true),
  dependency('wayland-server'),
  dependency('xkbcommon'),
  dependency('boost'),
]

subdir('src')

test('basic', exe)

