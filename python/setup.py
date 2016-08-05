import os
from distutils.core import setup, Extension

ext_module = Extension('_epc',
                       sources=['epc_wrap_python.cpp', 'src/epc.cpp'])

setup(name = 'epc',
      version = '0.1',
      description = "epc parsing lib",
      ext_modules = [ext_module],
      py_modules = ["epc"],
)

