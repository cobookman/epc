import os
from distutils.core import setup, Extension

ext_module = Extension('_epc',
                       sources=[
                           'epc_wrap_python.cpp',
                           'src/b64/cencode.cpp',
                           'src/gtin.cpp',
                           'src/epc.cpp',
                           'src/factory.cpp',
                           'src/encodings/sgtin.cpp',
                       ],
                       extra_compile_args=['-std=c++11'])

setup(name = 'epc',
      version = '0.1',
      description = "epc parsing lib",
      ext_modules = [ext_module],
      py_modules = ["epc"],
)

