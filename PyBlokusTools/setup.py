from setuptools import setup, find_packages # type: ignore
setup(
    name="PyBlokusTools",
    version="0.1",
    packages=find_packages(),
    package_data={'pyblokustools': ['data/*.json']}
)