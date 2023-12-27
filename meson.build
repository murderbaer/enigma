project('enigma', 'c')

unity_proj = subproject('unity')

project_source_files = [
  'src/enigma/rotor/rotor.c',
  'src/enigma/plugboard/plugboard.c',
  'src/enigma/reflector/reflector.c',
  'src/enigma/enigma.h',
  'src/helper/helper.c',
  'src/cli/cli.c',
  'src/server/server.c',
  'src/main.c',
]

executable('enigma', project_source_files)
