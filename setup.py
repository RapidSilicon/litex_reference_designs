#!/usr/bin/env python3

from setuptools import setup
from setuptools import find_packages


setup(
    name="litex",
    description="Python SoC/Core builder for building FPGA based systems.",
    author="Florent Kermarrec",
    author_email="florent@enjoy-digital.fr",
    url="http://enjoy-digital.fr",
    download_url="https://github.com/enjoy-digital/litex",
    test_suite="test",
    license="BSD",
    python_requires="~=3.6",
    install_requires=[
        "pyserial",
        "requests",
    ],
    packages=find_packages(exclude=("test*", "sim*", "doc*")),
    include_package_data=True,
    package_data={
        'litex.soc.doc': ['static/*']
    },
    platforms=["Any"],
    keywords="HDL ASIC FPGA hardware design",
    classifiers=[
        "Topic :: Scientific/Engineering :: Electronic Design Automation (EDA)",
        "Environment :: Console",
        "Development Status :: Alpha",
        "Intended Audience :: Developers",
        "License :: OSI Approved :: BSD License",
        "Operating System :: OS Independent",
        "Programming Language :: Python",
    ],
)
