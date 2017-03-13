from distutils.core import setup, Extension
# usage: python setup.pu build_ext --inplace

setup(ext_modules = [Extension("_sorts", ["_sorts.c", "sorts.c"])],)
