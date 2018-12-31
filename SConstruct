import os

# Other variables
cpppath = ['src/', 'thirdparty/']
libsuffix = ''

env = DefaultEnvironment(CPPPATH = cpppath)

# Functions
def file_tag_validator(key, value, env):
	if not value.isalnum():
		raise Exception("file_tag must be alphanumeric")
	if len(value) != 8:
		raise Exception("file_tag must be 8 exactly characters in length. actual length: %d" % len(value))

# Command line options
opts = Variables([], ARGUMENTS)
opts.Add(EnumVariable('platform', 'The target compilation platform', '', allowed_values=['', 'windows', 'linux', 'osx'], ignorecase=2))
opts.Add(EnumVariable('exclude_standard_data', 'Exclude the standard OctreePoint templates from compilation.', 'no', allowed_values=['yes', 'no'], ignorecase=2))
opts.Add(EnumVariable('octree_check_bounds', 'Perform boundary checks during Octree operations.', 'no', allowed_values=['yes', 'no'], ignorecase=2))

# Update the environment
opts.Update(env)
Help(opts.GenerateHelpText(env))

# Setup flags and targets
if env['exclude_standard_data'] == 'yes':
	env.Append(CPPDEFINES = ["BIGROCK_EXCLUDE_STANDARD_DATA"])
if env['octree_check_bounds'] == 'yes':
	env.Append(CPPDEFINES = ["BIGROCK_OCTREE_CHECK_BOUNDS"])

if env['platform'] == 'windows':
	env.Append(CCFLAGS = ["/EHsc"])
elif env['platform'] == '':
	print("Please specify a target platform (windows, linux, osx)")
	Exit(1)

# Setup sources
sources = []
for path in cpppath:
	sources += Glob(path + "*.cpp")

env.Object(sources)