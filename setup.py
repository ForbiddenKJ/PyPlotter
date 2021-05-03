from glob import glob
from setuptools import setup
from pybind11.setup_helpers import Pybind11Extension


ext_modules = [
    Pybind11Extension(
        "PyPlotter",
        sorted(glob("*.cpp")),
        library_dirs=["/usr/local/lib/", "/usr/lib/"],
        libraries=["raylib", "glfw3"],
    )
]

setup(ext_modules=ext_modules)
