import os
from distutils.core import setup, Extension

ext_module = Extension('_epc',
                       sources=['epc_wrap_python.cpp', 'epc.cpp'],
                       depends=['epc.h'],
                   )

setup(name = 'swig-epc-example',
       version = '0.1',
       description = "swig hello world example",
       ext_modules = [ext_module],
       py_modules = ["epc"],
)
