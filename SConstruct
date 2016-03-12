# lap, a functional style C++11 library for parsing command line arguments
# Created by Gil "gilzoide" Barbosa Reis

Help ("""
Welcome to lap scons build script
=================================

lap is the Lambda Argument Parser, a functional style C++11 library for parsing
command line arguments

Call with `scons debug=1` for a debug build (-g compiler flag)

When installing, there will be the library itself (.so), headers and pkg-config
script. Soon there will be man pages as well.

Everything can be uninstalled with `scons uninstall`
""")

if not GetOption ('help'):
    env = Environment (
        CXXFLAGS = '-Wall -pipe -O2 -std=c++11',
        CPPPATH = '#include',
        CXX = 'g++'
    )
    env.Decider ('MD5-timestamp')

    # if user pass debug=1, add -g flag for the compiler
    debug = ARGUMENTS.get ('debug', 0)
    if int (debug):
        env.Append (CXXFLAGS = ' -g')

    # build mosaic in the 'build' directory, without duplicating
    VariantDir ('build', 'src', duplicate = 0)
    SConscript ('build/SConscript', exports = 'env')

    # headers is defined in the SConscript file globally
    env.Command ("uninstall", None, Delete (FindInstalledFiles ()))

