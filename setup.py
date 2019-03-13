from distutils.core import setup, Extension

module1 = Extension('caramelrecolor',
	sources = ['src/caramelrecolor.c'])

setup (name = 'Caramel Recolor',
	version = '1.0',
	description = 'Reimplementation of the Gearhead Caramel recolor algorithm',
	author = 'Sander in \'t Veld',
	author_email = 'sander@abunchofhacks.coop',
	ext_modules = [module1])
