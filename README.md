# Bitprim C-API Library <a target="_blank" href="https://gitter.im/bitprim/Lobby">![Gitter Chat][badge.Gitter]</a>

*Bitcoin, Bitcoin Cash and Litecoin full node C-API library*

| **master(linux/osx)** | **dev(linux/osx)**   | **master(windows)**   | **dev(windows)** |
|:------:|:-:|:-:|:-:|
| [![Build Status](https://travis-ci.org/bitprim/bitprim-node-cint.svg)](https://travis-ci.org/bitprim/bitprim-node-cint)       | [![Build StatusB](https://travis-ci.org/bitprim/bitprim-node-cint.svg?branch=dev)](https://travis-ci.org/bitprim/bitprim-node-cint?branch=dev)  | [![Appveyor Status](https://ci.appveyor.com/api/projects/status/github/bitprim/bitprim-node-cint?svg=true)](https://ci.appveyor.com/project/bitprim/bitprim-node-cint)  | [![Appveyor StatusB](https://ci.appveyor.com/api/projects/status/github/bitprim/bitprim-node-cint?branch=dev&svg=true)](https://ci.appveyor.com/project/bitprim/bitprim-node-cint?branch=dev)  |

In version2, the `bitcoin-node` console app is for demonstration purposes only. See [bitprim-server](https://github.com/bitprim/bitprim-server) for release quality full node functionality.

Table of Contents
=================

   * [Bitprim Node-cint](#bitprim-node-cint)
      * [Installation](#installation)
        * [Using Conan](#using-conan-recommended)
        * [Build from source](#build-from-source)
            * [Debian/Ubuntu](#debianubuntu)
            * [Windows with Visual Studio](#windows-with-visual-studio)

## Installation

### Using Conan (recommended)

Conan is a Python package for dependency management; it only requires Python and Pip.
With Conan, install can be performed on any OS. If there are no prebuilt binaries for a given
OS-compiler-arch combination, Conan will build from source.

```
pip install conan
conan remote add bitprim https://api.bintray.com/conan/bitprim/bitprim
conan install bitprim-node-cint/0.1@bitprim/stable
```

The last step will install binaries and headers in Conan's cache, a directory outside the usual
system paths. This will avoid conflict with system packages such as boost.
Also, notice it references the stable version 0.1. To see which versions are available,
please check [Bintray](https://bintray.com/bitprim/bitprim/bitprim-node-cint%3Abitprim).

### Build from sources

#### Debian/Ubuntu

Make sure you have installed [bitprim-core](https://github.com/bitprim/bitprim-core), [bitprim-database](https://github.com/bitprim/bitprim-database), [bitprim-blockchain](https://github.com/bitprim/bitprim-blockchain), [bitprim-consensus](https://github.com/bitprim/bitprim-consensus) (optional), [bitprim-network](https://github.com/bitprim/bitprim-network) and [bitprim-node](https://github.com/bitprim/bitprim-node) beforehand according to their build instructions.

```
$ git clone https://github.com/bitprim/bitprim-node-cint.git
$ cd bitprim-node-cint
$ mkdir build
$ cd build
$ cmake .. -DENABLE_TESTS=OFF -DWITH_TESTS=OFF -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS="-std=c++11" 
$ make -j2
$ sudo make install
```

bitprim-node-cint is now installed in `/usr/local/`.

#### Windows with Visual Studio

This project, unlike secp256k1, has external dependencies such as boost.
The easiest way to build them is to use Conan from the CMake script,
which will install boost and other libraries in non-system directories.

From a [Visual Studio Developer Command Prompt](https://docs.microsoft.com/en-us/dotnet/framework/tools/developer-command-prompt-for-vs):

```
$ pip install conan
$ git clone https://github.com/bitprim/bitprim-node-cint.git
$ cd bitprim-node-cint
$ mkdir build
$ cd build
$ conan install ..
$ cmake .. -DUSE_CONAN=ON -DNO_CONAN_AT_ALL=OFF
$ msbuild ALL_BUILD.vcxproj
```

[badge.Gitter]: https://img.shields.io/badge/gitter-join%20chat-blue.svg
