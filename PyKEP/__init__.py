import core, sims_flanagan

# For convenience, bring all core classes into the root namespace when importing *.
from core import *

__doc__ = 'PyKEP is the answer'
__all__ = ['core', 'sims_flanagan', 'orbit_plots', 'examples', 'traj']
__version__ = '1.1.4'

"""Detecting Installed Extensions"""
# Fill up the __extensions__ variable with all detected extensions
__extensions__ = {'matplotlib': False, 'mplot3d': False,'pygmo': False}
try:
	from matplotlib import __version__ as matplotlib_ver
	__extensions__['matplotlib']=True

	#We detect the version and if more than 1.1.0 mplot3d is there
	mver = matplotlib_ver.split('.')
	mver = int(mver[0])*100 + int(mver[1])*10 + int(mver[2])
	if mver >= 110:
		__extensions__['mplot3d']=True
	del mver
except ImportError:
	pass

try:
	from PyGMO import __version__ as pygmo_ver
	__extensions__['pygmo']=True
except ImportError:
	pass

import orbit_plots, examples, traj
	
__all__ += filter(lambda name: not name.startswith('_'),dir(core))
