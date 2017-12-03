# lap, a functional style C++11 library for parsing command line arguments
# Created by Gil "gilzoide" Barbosa Reis

Help ("""
Welcome to lap scons build script
=================================

lap is the Lambda Argument Parser, a functional style C++11 library for parsing
command line arguments

Call with `scons Debug=1` for a debug build (-g compiler flag)

When installing, there will be the library itself, headers and pkg-config
script. Anytime there will be man pages as well.

Everything can be uninstalled with `scons uninstall`
""")

if not GetOption ('help'):
    # Add prefix changing option
    AddOption('--prefix',
            dest = 'prefix',
            type = 'string',
            nargs = 1,
            action = 'store',
            metavar = 'DIR',
            help = 'installation prefix')

    env = Environment (
        CXXFLAGS = '-Wall -pipe -O2 -std=c++11',
        CPPPATH = '#include',
        CXX = 'g++',
        PREFIX = GetOption ('prefix')
    )
    env.Decider ('MD5-timestamp')

    # if user pass Debug=1, add -g flag for the compiler
    debug = ARGUMENTS.get ('Debug', 0)
    if int (debug):
        env.Append (CXXFLAGS = ' -g')

    # build lap in the 'build' directory, without duplicating
    VariantDir ('build', 'src', duplicate = 0)
    SConscript ('build/SConscript', exports = 'env')

    # headers is defined in the SConscript file globally
    env.Command ("uninstall", None, Delete (FindInstalledFiles ()))

