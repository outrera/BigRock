import os

# Other variables
cpppath = ['src/', 'thirdparty/']
libsuffix = ''

# Functions

# Command line options
opts = Variables([], ARGUMENTS)
opts.Add(EnumVariable('platform', 'The target compilation platform', '', allowed_values=['', 'windows', 'linux', 'osx'], ignorecase=2))
opts.Add(EnumVariable('build', 'What type of build to run', 'object', allowed_values=['object', 'static', 'dynamic', 'shared'], ignorecase=2))
opts.Add(EnumVariable('target', 'The compilation target', 'debug', allowed_values=['debug', 'release'], ignorecase=2))
opts.Add(PathVariable('target_path', 'The location to place the resulting library (if a library is built).', 'bin/bigrock', PathVariable.PathAccept))
opts.Add(EnumVariable('vector3_type', 'The type to use for Vector3\'s xyz coordinates', 'float', allowed_values=['float', 'double', 'long_double'], ignorecase=2))
opts.Add(PathVariable('build_test', 'The name of the test source file (stored in tests) to build', '', PathVariable.PathAccept))
opts.Add(EnumVariable('use_mingw', 'Whether or not to use MinGW on Windows systems', 'no', allowed_values=['yes', 'no'], ignorecase=2))

# Update the environment
env = Environment(CPPPATH = cpppath)
opts.Update(env)
if env['use_mingw'] == 'yes':
	env = Environment(CPPPATH = cpppath, tools = ['mingw'])
	opts.Update(env)
Help(opts.GenerateHelpText(env))

# Setup flags and targets
if env['vector3_type'] == 'long_double':
	env.Append(CPPDEFINES = [("BIGROCK_VEC3_TYPE_ENUM", "BIGROCK_LONG_DOUBLE_ENUM")])
elif env['vector3_type'] == 'double':
	env.Append(CPPDEFINES = [("BIGROCK_VEC3_TYPE_ENUM", "BIGROCK_DOUBLE_ENUM")])
else:
	env.Append(CPPDEFINES = [("BIGROCK_VEC3_TYPE_ENUM", "BIGROCK_FLOAT_ENUM")])

if env['platform'] == 'windows' and env['use_mingw'] == 'no':
	env.Append(CCFLAGS = ["/EHsc"])
	if env['target'] == 'debug':
		env.Append(LINKFLAGS = ["/DEBUG"])

elif env['platform'] == 'linux' or env['platform'] == 'osx' or (env['platform'] == 'windows' and env['use_mingw'] == 'yes'):
	if env['platform'] == 'windows':
		env.Tool('mingw')
		env.Append(LINKFLAGS = ['-static-libstdc++', '-static-libgcc'])
	env.Append(CCFLAGS = '-std=gnu++98')
	if env['target'] == 'debug':
		env.Append(CCFLAGS = ['-g'])
		
elif env['platform'] == '':
	print("Please specify a target platform (windows, linux, osx)")
	Exit(1)

if env['target'] == 'debug':
	pass
else:
	env.Append(CPPDEFINES = ["NDEBUG"])

# Setup sources
sources = []
for path in cpppath:
	sources += Glob(path + "*.cpp")

if env['build_test'] != '':
	env.Program(source = sources + ["tests/" + env['build_test'] + ".cpp"], target = 'bin/' + env['build_test'])
elif env['build'] == 'object':
	env.Object(source = sources)
elif env['build'] == 'static':
	env.StaticLibrary(source = sources, target = env['target_path'])
elif env['build'] == 'dynamic' or env['build'] == 'shared':
	env.SharedLibrary(source = sources, target = env['target_path'])