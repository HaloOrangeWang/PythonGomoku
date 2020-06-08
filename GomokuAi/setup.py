# used to build Python Modules on Linux distributions.
from distutils.core import setup,Extension

MOD = 'example'
setup(name=MOD,
      version='1.0',
      headers=['./ai.h', './constants.h'],
      ext_modules=[Extension(MOD,sources=['./ai.cpp','./constants.cpp', './gomokuai.cpp'],
                  extra_compile_args=['-O0','-g'])])