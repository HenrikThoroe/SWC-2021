# SWC-2021

## Installation

### Docker

To (re)build and start a docker container with installed dev-tools run 

```sh
./docker-start.sh
```

### Custom

To install all required dependencies and dev-tools in a custom Linux environment run

```sh
./env-setup.sh
```

**Note**: A distro which supports binutils >= 2.33 and python >= 3.8 is required. For example Ubuntu 20.04 (focal) or Debian 11 (bullseye).


## Usage

For a good developer experience the usage of the custom compiler scripts located in `/PyBlokusTools` is recommended.
Those are Python scripts which are installed when following the [installation instructions](#Installation).
The following commands are available:

```sh
# Run all tests located in ./app/tests
blokustest

# Run all benchmarks located in ./app/tests
blokusbench

# Create a debug build of the client
blokusdebug

# Create an optimized build and run it with debug flag and log file support
blokusrun

# Create a production build of the client and prepare for upload
blokusprod

# Run mass tests with two clients competing
blokusmass

# Create the documentation from ./docsrc
blokusdoc
```

For more detailed information about available flags use `blokus* --help` where `*` should be replaced with `test`, `bench`, ...

You can setup your development environment using `source ./dev-setup`. It will install some handy aliases for a better workflow.
