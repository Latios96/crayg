# crayg
[![Build Status](https://travis-ci.com/Latios96/crayg.svg?token=fvycq6PG6anYyQZpnfAt&branch=master)](https://travis-ci.com/Latios96/crayg)
[![Build Status](https://github.com/Latios96/crayg/workflows/Github%20Actions%20CI/badge.svg)](https://github.com/Latios96/crayg/workflows/ccpp/badge.svg)


Personal Raytracer project to get familiar with C++ in general and how to do CI and TDD in C++.

![demo image](images/three_spheres_with_disk_light.0007.png)
## Building
### Prerequisites
This project uses [Conan](https://conan.io/), a C++ Package Manager, to manage its dependencies.
Conan is written in Python, so you can install it easily with pip:
```shell
pip install conan
```
You also need to add some additional remotes. Otherwise conan can not find all dependencies.
```shell
conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan
conan remote add ppodsiadly https://api.bintray.com/conan/ppodsiadly/conan
```

### Linux & Mac OS
```shell
mkdir build
cd build
cmake ..
make -j 4
```

### Windows (experimental)
```shell
mkdir build
cd build
cmake -G "Visual Studio 15 2017 Win64" .. --build
```

Run the tests
```shell
cd build
ctest -V
```

