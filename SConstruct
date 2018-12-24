import os

# Other variables
cpppath = ['src/', 'thirdparty/']
libsuffix = ''

env = DefaultEnvironment(CPPPATH = cpppath)

# Command line options
#opts = Variables([], ARGUMENTS)

# Update the environment
#opts.Update(env)
#Help(opts.GenerateHelpText(env))

# Check options

# Setup flags and targets

# Setup sources
sources = []
for path in cpppath:
	sources += Glob(path + "*.cpp")

env.Object(sources)