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
# This library is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this library.  If not, see <https://www.gnu.org/licenses/>.
#
# [authors:]
# Sander in 't Veld (sander@abunchofhacks.coop)
#

from distutils.core import setup, Extension

module1 = Extension('caramelrecolor',
	sources = ['src/caramelrecolor.c'])

setup (name = 'Caramel Recolor',
	version = '1.0',
	description = 'Reimplementation of the Gearhead Caramel recolor algorithm',
	author = 'Sander in \'t Veld',
	author_email = 'sander@abunchofhacks.coop',
	url = 'https://github.com/abunchofhacks/caramel-recolor',
	license = 'LGPLv3+',
	ext_modules = [module1])
