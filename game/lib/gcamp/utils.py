# Copyright 2010-2011 Ilkka Halila
# This file is part of Goblin Camp.
# 
# Goblin Camp is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Goblin Camp is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License 
# along with Goblin Camp. If not, see <http://www.gnu.org/licenses/>.
#
import sys, os

def _getModName(stackLevel):
	'Try to find mod name by inspecting given stack frame'
	
	frame    = sys._getframe(stackLevel)
	filename = frame.f_code.co_filename
	
	if 'mods' in filename:
		return os.path.basename(os.path.dirname(filename))
	else:
		return '<unknown>'

from importlib import machinery
from importlib import util

# This function reimplement beaviour of load_package from depricated Imp module
# Code copied from https://github.com/python/cpython/blob/3.11/Lib/imp.py#L200
# and updaed to work in our situatuin

def load_package(name, path):
	if os.path.isdir(path):
		extensions = (machinery.SOURCE_SUFFIXES[:] +
						machinery.BYTECODE_SUFFIXES[:])
		for extension in extensions:
			init_path = os.path.join(path, '__init__' + extension)
			if os.path.exists(init_path):
				path = init_path
				break
		else:
			raise ValueError('{!r} is not a package'.format(path))
	spec = util.spec_from_file_location(name, path,
										submodule_search_locations=[])
	if name in sys.modules:
		module = sys.modules[name]
		spec.loader.exec_module(module)
		return module
	else:
		module = util.module_from_spec(spec)
		sys.modules[name] = module
		spec.loader.exec_module(module)
		return module

