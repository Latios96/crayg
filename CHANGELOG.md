# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]
## 1.3.0
### Added
- Camera: added more tests
- added generate_coverage.sh script
- TriangleMesh: added tests for serialize/deserialize
- SceneWriter: test with camera
### Changed
- TriangleMesh: use BoundingBix for intersection
- JsonSceneWriter now uses exceptions
- JsonDeserializer now uses exceptions
- Test files are now in UpperCamelCase
- Stopwatch now uses a callback to print the time. This way we can use the logger
## 1.2.0
### Added
- added RemainingTimeCalculator class
- add build_clean script for centos
### Changed
- time remaining is now printed during rendering
## 1.1.0
### Added
- Triangle intersection
## 0.2.0
### Added
- respect light intensity in lambert
- scene now contains the camera
- warning when reading if attribute does not exists
- proper virtual class for CameraModel
- Maya export script
- triangle Intersection
### Changed
- made architecture more useful
- mirror x axis to match maya
### Fixed
- sphere would move down in image when positive y coordinate
## [0.1.0]
### Added
- added tests for BmpImageWriter
- SceneIntersector: added tests
- SceneWriter: added tests
- JsonSerializer: Created abstract class SerializerImplementation for better abstraction
- ImageWriter: added virtual destructor
- Added Renderer Class
- Add logger support
- Added CLI interface, reads scene from cli args
- Sphere Intersection returns Ray
- added support for simple lights
- added support for simple lambert shading

## [0.1.0]
### Added
- Easy scene serialization
- Changelog.md
### Changed
- removed Prim-Stage-Schema Experiments

