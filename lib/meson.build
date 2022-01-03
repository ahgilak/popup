project('popup', 'c',
          version: '0.1.0',
    meson_version: '>= 0.50.0',
  default_options: [ 'warning_level=2',
                     'c_std=gnu11',
                     'buildtype=release',
                   ],
)

add_project_arguments([
  '-I' + meson.build_root(),
], language: 'c')

popup_sources = [
  'popup.c',
]

popup_deps = [
  dependency('gtk4'),
]

gnome = import('gnome')

popup_sources += gnome.compile_resources('popup-resources',
  'popup.gresource.xml',
  c_name: 'popup',
)

if get_option('buildtype') == 'debug'
  add_project_arguments('-DDEBUG', language : ['c'])
endif

popup_lib = shared_library('popup',
  popup_sources,
  dependencies: popup_deps,
  install: false,
)