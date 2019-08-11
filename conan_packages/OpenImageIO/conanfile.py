from conans import ConanFile, CMake, tools
import os

class OpenimageioConan(ConanFile):
    name = "OpenImageIO"
    version = "2.0.3"
    license = "BSD 3-clause"
    author = "Charles Barto <bartoc@umich.edu>"
    url = "https://github.com/barcharcraz/conan-packages"
    description = "Open Image IO library"
    topics = ("graphics", "images", "IO")
    settings = "os", "compiler", "build_type", "arch"
    exports_sources = ["CMakeLists.txt"]
    options = {
        "shared": [True, False],
        "fPIC": [True, False]
    }
    default_options = {
        "shared": False,
        "fPIC": True,
        "boost:without_filesystem": False,
        "boost:without_system": False,
        "boost:without_regex": False
    }
    generators = "cmake"

    requires = (
        "boost/[>=1.56.0]@conan/stable",
        "libtiff/4.0.9@bincrafters/stable",
        "libpng/1.6.34@bincrafters/stable",
        "openexr/2.3.0@conan/stable",
        "libjpeg/9c@bincrafters/stable",
        "tsl-robin-map/0.6.1@tessil/stable"
    )

    _source_subfolder = "source_subfolder"
    _build_subfolder = "build_subfolder"


    def source(self):
        source_url = "https://github.com/OpenImageIO/oiio/archive/Release-{}.tar.gz".format(self.version)
        tools.get(source_url, sha256='b33a1e9d7ab34914e173a1dd97dc14889c05d2c057df8a54553a187300e0aa05')
        extracted_dir = "oiio-Release-{}".format(self.version)
        os.rename(extracted_dir, self._source_subfolder)
        bad_cmake_files = [
            "{}/CMakeLists.txt".format(self._source_subfolder),
            "{}/src/libOpenImageIO/CMakeLists.txt".format(self._source_subfolder),
            "{}/src/include/CMakeLists.txt".format(self._source_subfolder)
        ]
        for f in bad_cmake_files:
            tools.replace_in_file(f, r"${CMAKE_SOURCE_DIR}", r"${PROJECT_SOURCE_DIR}", strict=False)
            tools.replace_in_file(f, r"${CMAKE_BINARY_DIR}", r"${PROJECT_BINARY_DIR}", strict=False)

    def _configure_cmake(self):
        cmake = CMake(self)
        cmake.definitions["OIIO_BUILD_TOOLS"] = False
        cmake.definitions["OIIO_BUILD_TESTS"] = False
        cmake.definitions["BUILDSTATIC"] = not self.options.shared
        cmake.definitions["EMBEDPLUGINS"] = True
        cmake.definitions["BUILD_MISSING_DEPS"] = False
        # not included in above for some reason
        cmake.definitions["BUILD_MISSING_ROBINMAP"] = False
        cmake.definitions["BUILD_MISSING_PYBIND11"] = False
        cmake.definitions["BUILD_TESTING"] = False
        cmake.definitions["USE_DICOM"] = False
        cmake.definitions["USE_FFMPEG"] = False
        cmake.definitions["USE_EXTERNAL_PUGIXML"] = False
        cmake.definitions["USE_GIF"] = False
        cmake.definitions["USE_FIELD3D"] = False
        cmake.definitions["USE_JPEGTURBO"] = False
        cmake.definitions["USE_FREETYPE"] = False
        cmake.definitions["USE_LIBRAW"] = False
        cmake.definitions["USE_NUKE"] = False
        cmake.definitions["USE_OPENCV"] = False
        cmake.definitions["USE_OPENJPEG"] = False
        cmake.definitions["USE_OCIO"] = False
        cmake.definitions["USE_TBB"] = False
        cmake.definitions["USE_OPENSSL"] = False
        cmake.definitions["USE_OPENVDB"] = False
        cmake.definitions["USE_OPENGL"] = False
        cmake.definitions["USE_PTEX"] = False
        cmake.definitions["USE_PYTHON"] = False
        cmake.definitions["USE_QT"] = False
        cmake.definitions["USE_SIMD"] = "0"
        cmake.definitions["USE_fPIC"] = self.options.fPIC
        cmake.definitions["LINKSTATIC"] = not self.options["boost"].shared
        cmake.configure(build_folder=self._build_subfolder)

        return cmake

    def build(self):
        cmake = self._configure_cmake()
        cmake.build()

    def package(self):
        cmake = self._configure_cmake()
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = tools.collect_libs(self)

