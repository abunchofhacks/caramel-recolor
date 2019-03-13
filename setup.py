#
# [setup.py]
#
# Setup for the caramelrecolor module.
#
# Part of the Caramel Recolor library
# developed by A Bunch of Hacks
# commissioned by Joseph Hewitt.
#
# Copyright (c) 2019 A Bunch of Hacks
#
# License to be determined.
#
# [authors:]
# Sander in 't Veld
#

from distutils.core import setup, Extension

module1 = Extension('caramelrecolor',
	sources = ['src/caramelrecolor.c'])

setup (name = 'Caramel Recolor',
	version = '1.0',
	description = 'Reimplementation of the Gearhead Caramel recolor algorithm',
	author = 'Sander in \'t Veld',
	author_email = 'sander@abunchofhacks.coop',
	ext_modules = [module1])
