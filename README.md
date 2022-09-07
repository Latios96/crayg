# crayg

[![Build Status](https://github.com/Latios96/crayg/workflows/Github%20Actions%20CI/badge.svg)](https://github.com/Latios96/crayg/workflows/ccpp/badge.svg)

Personal Raytracer project started to get familiar with C++ in general and how to do CI and TDD in C++.

![demo image](images/CornellBox_Original_GI.png)

Cornell Box by http://casual-effects.com/data/index.html

<!-- TOC -->

* [crayg](#crayg)
  * [Features](#features)
    * [Rendering related features](#rendering-related-features)
    * [Project features not related to rendering](#project-features-not-related-to-rendering)
  * [Build the project](#build-the-project)
    * [Prerequisites](#prerequisites)
    * [Build](#build)
      * [Linux & Mac OS](#linux--mac-os)
      * [Windows](#windows)
  * [Test execution](#test-execution)

<!-- TOC -->

## Features

### Rendering related features

- Sphere / Trianglemesh intersection
- Area lights (Rect and Disk)
- perfect reflections
- diffuse reflections / GI
- naive BVH implementation
- multiple integrators:
  - Raytracing
  - Ambient Occlusion
  - Debug (Simple "N Dot V shading", inspired
    by [Renderman's PxrVisualizer](https://rmanwiki.pixar.com/display/REN24/PxrVisualizer)))
- Scene format uses USD, with basic respect
  for [UsdRender](https://graphics.pixar.com/usd/release/api/usd_render_page_front.html)
- CLI interface / basic Renderview GUI

### Project features not related to rendering

- Unittests
- Integrationtests using [Cato](https://github.com/Latios96/cato)
- Continuous Integration using Github Actions
- support for Windows, Linux and Mac OS
- fully automated CMake build
- Support for CMake Unity builds
- Dependency Management using [Conan](https://conan.io/)
  - Conan Recipes for OpenSubdiv ([available](https://conan.io/center/opensubdiv) in Conan Center) and USD (to be
    contributed to Conan Center)
- Autodesk Maya GUI integration for easy authoring of integration test
  scenes [(more details)](docs/maya_test_integration.md)

## Build the project

### Prerequisites

- Conan Package Manager, get it [here](https://conan.io/downloads.html)
- CMake
- A C++ 17 compiler
- (access to my custom USD Conan recipe)

The invocation of Conan is handled transparently by CMake

### Build

For better buid speed, it is recommended to do a CMake unity build by
specifying `-DCMAKE_UNITY_BUILD=true -DCMAKE_UNITY_BUILD_BATCH_SIZE=16`

#### Linux & Mac OS

```shell
mkdir build
cd build
cmake -DCMAKE_UNITY_BUILD=true -DCMAKE_UNITY_BUILD_BATCH_SIZE=16 ..
make -j 4
```

#### Windows

```shell
mkdir build
cd build
cmake -G "Visual Studio 16 2019" -DCMAKE_UNITY_BUILD=true -DCMAKE_UNITY_BUILD_BATCH_SIZE=16 .. --build
```

## Test execution
```shell
cd build
ctest -V
```

