from setuptools import setup, find_packages
setup(
    name="PyBlokusTools",
    version="0.1",
    packages=find_packages(),
    package_data={'pyblokustools': ['data/*.json']}
)