from distutils.core import setup, Extension

module = Extension('BlenderActivity',
                    define_macros = [('MAJOR_VERSION', '1'),
                                     ('MINOR_VERSION', '0')],
                    include_dirs = ['./discord_files'],
                    libraries = ['discord_game_sdk.dll'],
                    library_dirs = ['../lib/x86_64'],
                    sources = ['DiscordTypes.cpp'])



setup(name = 'BlenderActivity',
       version = '1.0',
       description = 'A module to call Discord activity calls from Blender',
       author = 'Pratik Deolasi',
       ext_modules = [module])