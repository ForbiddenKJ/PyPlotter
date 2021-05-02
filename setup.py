from glob import glob
from setuptools import setup
from pybind11.setup_helpers import Pybind11Extension


ext_modules = [
    Pybind11Extension(
        "PyPlotter",
        sorted(glob("*.cpp")),
        #include_dirs=['/usr/local/include/'],
        library_dirs=['/usr/local/lib/'],
        libraries=['raylib'],
    )
]

setup(
    ext_modules=ext_modules
)
