import setuptools # type: ignore

from pyblokustools.version import VERSION

setuptools.setup(
    name="PyBlokusTools",
    version=VERSION,
    author="Rubin Raithel, Henrik Thorøe",
    author_email="dev@rubinraithel.de",
    description="Tools for the SWC-2021 Blokus Project",
    url="https://github.com/HenrikThoroe/SWC-2021/tree/master/scripts",
    packages=setuptools.find_packages(),
    classifiers=[
        "Programming Language :: Python :: 3",
        "License :: OSI Approved :: MIT License",
        "Operating System :: POSIX",
    ],
    python_requires='>=3.8',
    install_requires=[
        'Sphinx>=3.2.1',
        'sphinx-rtd-theme>=0.5.0',
        'breathe>=4.22.1',
    ],
    entry_points = {
        "console_scripts": [
            'blokustest = pyblokustools.scripts.runTests:runTests',
            'blokusbench = pyblokustools.scripts.runBenchmarks:runBenchmarks',
            'blokusprod = pyblokustools.scripts.compileProduction:compileProduction',
            'blokusdebug = pyblokustools.scripts.compileDebug:compileDebug',
            'blokusdoc = pyblokustools.scripts.makeDocumentation:makeDocumentation',
            'blokusrun = pyblokustools.scripts.run:run',
        ]
    },
)
