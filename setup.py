from distutils.core import setup, Extension

module1 = Extension('caramelrecolor',
	sources = ['src/caramelrecolor.c'])

setup (name = 'Caramel Recolor',
	version = '0.1',
	ext_modules = [module1])
